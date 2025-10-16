#include "cameramanager.h"


CameraManager::CameraManager() {
    m_sdkInitialized = false;
    m_stDevList.nDeviceNum = 0;
}

CameraManager::~CameraManager() {}



void CameraManager::initializeSDK()
{
    if (!m_sdkInitialized) {
        int nRet = HKCamera::InitSDK();
        if (nRet != MV_OK) {
            // qDebug() << "SDK Init Failed!";
            emit logMessage(QString("SDK Init Failed!"));
            return;
        }
        HKCamera::GetSDKVersion();
        m_sdkInitialized = true;
        // qDebug() << "SDK Initialized successfully.";
        emit logMessage(QString("SDK Initialized successfully!"));
    }
}


void CameraManager::findCamDevice(MV_CC_DEVICE_INFO_LIST* m_stDevList)
{
    initializeSDK();
    int nRet = HKCamera::EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE | MV_GENTL_GIGE_DEVICE | MV_GENTL_CAMERALINK_DEVICE |
                                         MV_GENTL_CXP_DEVICE | MV_GENTL_XOF_DEVICE ,m_stDevList);
    if (MV_OK != nRet)
    {
        return;
    }
    if (m_stDevList->nDeviceNum){
        // qDebug()<<"camera num: "<<m_stDevList->nDeviceNum;
        emit logMessage(QString("find camera num: %1").arg(m_stDevList->nDeviceNum));
        for (unsigned int i = 0; i < m_stDevList->nDeviceNum; i++)
        {
            MV_CC_DEVICE_INFO* pDeviceInfo = m_stDevList->pDeviceInfo[i];
            if (NULL == pDeviceInfo)
            {
                qDebug()<<"camera num:" <<i<<"无法获取！！！";
                continue;
            }
            if (pDeviceInfo->nTLayerType == MV_GIGE_DEVICE)
            {
                int nIp1 = ((pDeviceInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0xff000000) >> 24);
                int nIp2 = ((pDeviceInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0x00ff0000) >> 16);
                int nIp3 = ((pDeviceInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0x0000ff00) >> 8);
                int nIp4 = (pDeviceInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0x000000ff);
                // qDebug() << "CurrentIp:"
                //          << QString("%1.%2.%3.%4").arg(nIp1).arg(nIp2).arg(nIp3).arg(nIp4);
                // qDebug()<<"UserDefinedName:" <<pDeviceInfo->SpecialInfo.stGigEInfo.chUserDefinedName;


                QString msg = QString("Camera Ip: %1.%2.%3.%4").arg(nIp1).arg(nIp2).arg(nIp3).arg(nIp4);
                emit logMessage(msg);
            }
            else if (pDeviceInfo->nTLayerType == MV_USB_DEVICE)
            {
                qDebug() << "UserDefinedName:" << pDeviceInfo->SpecialInfo.stUsb3VInfo.chUserDefinedName;
                qDebug() << "Serial Number:" << pDeviceInfo->SpecialInfo.stUsb3VInfo.chSerialNumber;
                qDebug() << "Device Number:" << pDeviceInfo->SpecialInfo.stUsb3VInfo.nDeviceNumber;
            }
            else if (pDeviceInfo->nTLayerType == MV_GENTL_GIGE_DEVICE)
            {
                qDebug() << "UserDefinedName:" << pDeviceInfo->SpecialInfo.stUsb3VInfo.chUserDefinedName;
                qDebug() << "Serial Number:" << pDeviceInfo->SpecialInfo.stUsb3VInfo.chSerialNumber;
                qDebug() << "Model Number:" << pDeviceInfo->SpecialInfo.stGigEInfo.chModelName;
            }
            else if (pDeviceInfo->nTLayerType == MV_GENTL_CAMERALINK_DEVICE)
            {
                qDebug() << "UserDefinedName:" << pDeviceInfo->SpecialInfo.stUsb3VInfo.chUserDefinedName;
                qDebug() << "Serial Number:" << pDeviceInfo->SpecialInfo.stUsb3VInfo.chSerialNumber;
                qDebug() << "Model Number:" << pDeviceInfo->SpecialInfo.stGigEInfo.chModelName;
            }
            else if (pDeviceInfo->nTLayerType == MV_GENTL_CXP_DEVICE)
            {
                qDebug() << "UserDefinedName:" << pDeviceInfo->SpecialInfo.stUsb3VInfo.chUserDefinedName;
                qDebug() << "Serial Number:" << pDeviceInfo->SpecialInfo.stUsb3VInfo.chSerialNumber;
                qDebug() << "Model Number:" << pDeviceInfo->SpecialInfo.stGigEInfo.chModelName;
            }
            else if (pDeviceInfo->nTLayerType == MV_GENTL_XOF_DEVICE)
            {
                qDebug() << "UserDefinedName:" << pDeviceInfo->SpecialInfo.stUsb3VInfo.chUserDefinedName;
                qDebug() << "Serial Number:" << pDeviceInfo->SpecialInfo.stUsb3VInfo.chSerialNumber;
                qDebug() << "Model Number:" << pDeviceInfo->SpecialInfo.stGigEInfo.chModelName;
            }
            else
            {
                qDebug()<<"Not support.";
            }
        }
    }
    else
    {
        printf("Find No Devices!\n");
        return;
    }
    emit searchFinished(m_stDevList->nDeviceNum);
}
