#include "camerause.h"
#include "hkcamera.h"
#include "imageprocess.h"

CameraUse::CameraUse(QObject* parent): QObject(parent) {

}

CameraUse::~CameraUse() {
}

void CameraUse::setCamera(HKCamera* camera)
{
    HKCamera_ = camera;
}

void CameraUse::stop()
{
    isRunning_ = false;
}

void CameraUse::processCamera(){
    if (!HKCamera_) {
        qDebug() << "HKCamera_ is nullptr!";
        emit logMessage("Error: HKCamera_ 未初始化！");
        emit finished();
        return;
    }

    isRunning_ = true;
    qDebug() << "Camera thread started.";

    MV_FRAME_OUT stImageInfo = {0};
    MV_CC_IMAGE   stImageData = {0};
    int nRet = MV_OK;
    cv::Mat matImage;
    qDebug()<<"start";
    while(isRunning_)
    {
        nRet = HKCamera_->GetImageBuffer(&stImageInfo, 1000);
        if (MV_OK != nRet)
        {
            emit logMessage(QString("取流失败 code=%1").arg(nRet));
            continue;
        }
        stImageData.nWidth = stImageInfo.stFrameInfo.nExtendWidth;
        stImageData.nHeight = stImageInfo.stFrameInfo.nExtendHeight;
        stImageData.enPixelType = stImageInfo.stFrameInfo.enPixelType;
        stImageData.nImageLen = stImageInfo.stFrameInfo.nFrameLenEx;
        stImageData.pImageBuf = stImageInfo.pBufAddr;

        MV_FRAME_OUT_INFO_EX frame = stImageInfo.stFrameInfo;
        unsigned char* pData = stImageInfo.pBufAddr;



        if (frame.enPixelType == PixelType_Gvsp_Mono8)
        {
            matImage = cv::Mat(frame.nHeight, frame.nWidth, CV_8UC1, pData);
        }
        else if (frame.enPixelType == PixelType_Gvsp_BGR8_Packed)
        {
            matImage = cv::Mat(frame.nHeight, frame.nWidth, CV_8UC3, pData);
        }
        else
        {
            // qDebug() << "Unsupported pixel format:" << frame.enPixelType;
            emit logMessage(QString("不支持的像素格式：%1").arg(frame.enPixelType));
            HKCamera_->FreeImageBuffer(&stImageInfo);
            emit finished();
            return;
        }
        QImage img = ImageProcess::MatToQImage(matImage);
        emit sendImage(img);
        QString msg = QString("帧号: %1, 大小: %2x%3")
                          .arg(frame.nFrameNum)
                          .arg(frame.nWidth)
                          .arg(frame.nHeight);
        emit logMessage(msg);

        HKCamera_->FreeImageBuffer(&stImageInfo);
    }
    HKCamera_->StopGrabbing();
    emit logMessage("Camera thread stopped.");
    emit finished();
}
