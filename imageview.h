#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H
#include <QObject>
#include <opencv2/opencv.hpp>
#include <QImage>
#include <QDebug>
#include <QThread>
#include "imageprocess.h"

using namespace cv;

class ImageView:public QObject
{
    Q_OBJECT
public:
    ImageView();
    ~ImageView();

    void setPath(const QString &path);



public slots:
    void processImage();  // 按钮触发的槽函数
    void processVideo();
    void stop();  // 停止视频播放

signals:
    void sendImage(const QImage &image);
    void finished();
    void logMessage(const QString &msg);

private:
    QString filePath;
    bool stopFlag = false;
    int frameCount;
    cv::VideoCapture cap;
};

#endif // IMAGEVIEW_H
