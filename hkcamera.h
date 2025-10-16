#ifndef HKCAMERA_H
#define HKCAMERA_H

#include <QObject>

#include "MvCameraControl.h"

class HKCamera:public QObject
{
    Q_OBJECT
public:
    HKCamera();
    ~HKCamera();


public:
    // ch:初始化SDK | en:Initialize SDK
    static int InitSDK();

    // ch:反初始化SDK | en:Finalize SDK
    static int FinalizeSDK();

    // ch:获取SDK版本号 | en:Get SDK Version
    static int GetSDKVersion();

    // ch:枚举设备 | en:Enumerate Device
    static int EnumDevices(unsigned int nTLayerType, MV_CC_DEVICE_INFO_LIST* pstDevList);

    // ch:判断设备是否可达 | en:Is the device accessible
    static bool IsDeviceAccessible(MV_CC_DEVICE_INFO* pstDevInfo, unsigned int nAccessMode);

    // ch:打开设备 | en:Open Device
    int Open(MV_CC_DEVICE_INFO* pstDeviceInfo);

    // ch:关闭设备 | en:Close Device
    int Close();

    // ch:判断相机是否处于连接状态 | en:Is The Device Connected
    bool IsDeviceConnected();

    // ch:注册图像数据回调 | en:Register Image Data CallBack
    int RegisterImageCallBack(void(__stdcall* cbOutput)(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser), void* pUser);

    int RegisterImageCallBack2(void(__stdcall* cbOutput)(MV_FRAME_OUT* pstFrame, void *pUser, bool bAutoFree), void* pUser, bool bAutoFree);

    // ch:开启抓图 | en:Start Grabbing
    int StartGrabbing();

    // ch:停止抓图 | en:Stop Grabbing
    int StopGrabbing();

    // ch:主动获取一帧图像数据 | en:Get one frame initiatively
    int GetImageBuffer(MV_FRAME_OUT* pFrame, int nMsec);

    // ch:释放图像缓存 | en:Free image buffer
    int FreeImageBuffer(MV_FRAME_OUT* pFrame);

    // ch:显示一帧图像 | en:Display one frame image
    int DisplayOneFrame(void* hDisplay, MV_CC_IMAGE* pImageInfo);

    // ch:设置SDK内部图像缓存节点个数 | en:Set the number of the internal image cache nodes in SDK
    int SetImageNodeNum(unsigned int nNum);

    // ch:获取设备信息 | en:Get device information
    int GetDeviceInfo(MV_CC_DEVICE_INFO* pstDevInfo);

    // ch:获取GEV相机的统计信息 | en:Get detect info of GEV camera
    int GetGevAllMatchInfo(MV_MATCH_INFO_NET_DETECT* pMatchInfoNetDetect);


    // ch:获取和设置Int型参数，如 Width和Height
    // en:Get Int type parameters, such as Width and Height
    int GetIntValue(IN const char* strKey, OUT MVCC_INTVALUE_EX *pIntValue);
    int SetIntValue(IN const char* strKey, IN int64_t nValue);

    // ch:获取和设置Enum型参数，如 PixelFormat
    // en:Get Enum type parameters, such as PixelFormat
    int GetEnumValue(IN const char* strKey, OUT MVCC_ENUMVALUE *pEnumValue);
    int SetEnumValue(IN const char* strKey, IN unsigned int nValue);
    int SetEnumValueByString(IN const char* strKey, IN const char* sValue);
    int GetEnumEntrySymbolic(IN const char* strKey, IN MVCC_ENUMENTRY* pstEnumEntry);

    // ch:获取和设置Float型参数，如 ExposureTime和Gain
    // en:Get Float type parameters, such as ExposureTime and Gain
    int GetFloatValue(IN const char* strKey, OUT MVCC_FLOATVALUE *pFloatValue);
    int SetFloatValue(IN const char* strKey, IN float fValue);

    // ch:获取和设置Bool型参数，如 ReverseX
    // en:Get Bool type parameters, such as ReverseX
    int GetBoolValue(IN const char* strKey, OUT bool *pbValue);
    int SetBoolValue(IN const char* strKey, IN bool bValue);

    // ch:探测网络最佳包大小(只对GigE相机有效) | en:Detection network optimal package size(It only works for the GigE camera)
    int GetOptimalPacketSize(unsigned int* pOptimalPacketSize);

    // ch:注册消息异常回调 | en:Register Message Exception CallBack
    int RegisterExceptionCallBack(void(__stdcall* cbException)(unsigned int nMsgType, void* pUser), void* pUser);

    // ch:注册单个事件回调 | en:Register Event CallBack
    int RegisterEventCallBack(const char* pEventName, void(__stdcall* cbEvent)(MV_EVENT_OUT_INFO * pEventInfo, void* pUser), void* pUser);
private:
    void* m_hDevHandle;
};

#endif // HKCAMERA_H
