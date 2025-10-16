#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include <QObject>
#include <opencv2/opencv.hpp>
#include <QImage>
#include <QDebug>
#include <QThread>
#include "hkcamera.h"

class CameraManager: public QObject
{
    Q_OBJECT
public:
    CameraManager();
    ~CameraManager();
    // 初始化和反初始化SDK，由外部调用
    void initializeSDK();

public slots:
    // 查找设备的槽函数
    void findCamDevice(MV_CC_DEVICE_INFO_LIST* m_stDevList);

signals:
    // 设备查找完成（无论成功与否）后发射
    void searchFinished(int deviceCount);

    void logMessage(const QString &msg);

private:
    MV_CC_DEVICE_INFO_LIST m_stDevList;
    bool m_sdkInitialized;
};

#endif // CAMERAMANAGER_H
