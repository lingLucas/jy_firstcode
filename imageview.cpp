#include "imageview.h"

ImageView::ImageView() {}

ImageView::~ImageView() {}


void ImageView::processImage() {
    cv::Mat img = cv::imread(filePath.toStdString());
    // cv::imshow("show", img);
    // qDebug()<<img.cols<<","<<img.rows;
    if (img.empty()) {
        QString msg = QString("无法打开图片:%1").arg(filePath);
        qDebug() << "无法加载图片，错误路径：" << filePath;
        emit logMessage(msg);
        return;
    }

    // 转换为 Qt 图像
    // qDebug() << "发射 sendImage 信号";
    QImage qimg = ImageProcess::MatToQImage(img);
    // 发射信号
    emit sendImage(qimg);
    QString msg = QString("图片加载成功:%1").arg(filePath);
    // qDebug()<<msg;
    emit logMessage(msg);
}


void ImageView::setPath(const QString &path) {
    filePath = path;
}

void ImageView::processVideo()
{
    if (filePath.isEmpty()) {
        // qDebug() << "video path is empty!";
        QString msg = QString("video path is empty!");
        emit logMessage(msg);
        emit finished();
        return;
    }
    frameCount = 0;
    cap.open(filePath.toStdString());
    if (!cap.isOpened()) {
        QString msg = QString("无法打开视频:%1").arg(filePath);
        emit logMessage(msg);
        emit finished();
        return;
    }

    cv::Mat frame;
    while (!stopFlag && cap.read(frame)) {
        if (frame.empty()) break;

        // ✅ 这里可以插入检测逻辑，例如 YOLO 推理：
        // cv::Mat result = detect(frame);
        frameCount++;
        QImage img = ImageProcess::MatToQImage(frame);
        emit sendImage(img);
        QString msg = QString("frame=%1 ,检测到缺陷数量%2").arg(frameCount).arg(20);
        emit logMessage(msg);

        QThread::msleep(30); // 控制播放速度 (约33ms对应30FPS)
    }

    cap.release();
    emit finished();
}


void ImageView::stop() {
    stopFlag = true;
}
