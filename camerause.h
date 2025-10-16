#ifndef CAMERAUSE_H
#define CAMERAUSE_H

#include <QObject>
#include <opencv2/opencv.hpp>
#include <QImage>
#include <QDebug>
#include <QThread>
#include "hkcamera.h"

using namespace cv;

class CameraUse:public QObject
{
    Q_OBJECT
public:
    explicit CameraUse( QObject* parent = nullptr);
    ~CameraUse();

public:
    void setCamera(HKCamera* camera);  // 外部传入相机指针
    void stop();


public slots:
    void processCamera();

signals:
    void sendImage(const QImage &image);
    void logMessage(const QString &msg);
    void finished();


private:
    HKCamera *HKCamera_ = nullptr;
    bool isRunning_ = false;
};

#endif // CAMERAUSE_H
