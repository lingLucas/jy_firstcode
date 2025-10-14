#include "imageview.h"

ImageView::ImageView() {}

ImageView::~ImageView() {}

//Mat转图像
QImage ImageView::MatToQImage(const cv::Mat& mat)
{
    // 8-bits unsigned, NO. OF CHANNELS = 1
    if (mat.type() == CV_8UC1)
    {
        QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
        image.setColorCount(256);
        for (int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgb(i, i, i));
        }
        // Copy input Mat
        uchar *pSrc = mat.data;
        for (int row = 0; row < mat.rows; row++)
        {
            uchar *pDest = image.scanLine(row);
            memcpy(pDest, pSrc, mat.cols);
            pSrc += mat.step;
        }
        return image;
    }
    // 8-bits unsigned, NO. OF CHANNELS = 3
    else if (mat.type() == CV_8UC3)
    {
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return image.rgbSwapped();
    }
    else if (mat.type() == CV_8UC4)
    {
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        return image.copy();
    }
    else
    {
        return QImage();
    }
}


Mat ImageView::QImageToCvMat(const QImage &image, bool cloneImageData)
{
    switch (image.format())
    {
    // 8-bit, 4 channel (RGBA)
    case QImage::Format_ARGB32:
    case QImage::Format_ARGB32_Premultiplied:
    {
        cv::Mat mat(image.height(), image.width(),
                    CV_8UC4,
                    (void*)image.constBits(),
                    image.bytesPerLine());
        return (cloneImageData ? mat.clone() : mat);
    }

    // 8-bit, 3 channel (RGB888)
    case QImage::Format_RGB32:
    case QImage::Format_RGB888:
    {
        QImage swapped = image;
        if (image.format() == QImage::Format_RGB888)
            swapped = image.rgbSwapped(); // Qt是RGB，OpenCV默认BGR

        cv::Mat mat(swapped.height(), swapped.width(),
                    CV_8UC3,
                    (void*)swapped.constBits(),
                    swapped.bytesPerLine());
        return (cloneImageData ? mat.clone() : mat);
    }

    // 8-bit, 1 channel (grayscale)
    case QImage::Format_Indexed8:
    {
        cv::Mat mat(image.height(), image.width(),
                    CV_8UC1,
                    (void*)image.constBits(),
                    image.bytesPerLine());
        return (cloneImageData ? mat.clone() : mat);
    }

    default:
        qWarning() << "QImageToCvMat() - Unsupported QImage format:"
                   << image.format();
        return cv::Mat();
    }
}


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
    QImage qimg = MatToQImage(img);
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
        QImage img = MatToQImage(frame);
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
