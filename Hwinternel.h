#ifndef VIDEO_CAPTURE_H
#define VIDEO_CAPTURE_H
#include <linux/videodev2.h>
#include <media/cam_defs.h>
#include <media/cam_sensor.h>
#include <media/cam_lrme.h>
#include <media/cam_defs.h>
#include <media/cam_isp.h>
#include <media/cam_req_mgr.h>
#include <media/cam_sync.h>
#include "types.h"


static const INT   MaxDevName              = 64;  ///< Max size of a KMD device name
static const INT32  CSLHwMaxDevOpenPolls   = 5;                         ///< Maximum device open poll attempts
static const INT32  maxSleepTime = 100000;
static const INT32  EBUSY_CODE             = 114;                       ///< Error code number for operation already in progress

// @brief CSLHw KMD device classifications.
typedef enum
{
    InternalHwVideodevice = 0,     ///< This CSLHw KMD device of type v4l video device
    InternalHwVideoSubdevice,      ///< This CSLHw KMD device of type v4l subdev device
    InternalHwVideoSubdeviceAll,   ///< This CSLHw KMD device of type v4l all subdev devices
    InternalHwVideoInvalid         ///< This is upper bound check value
} HwInternalHwEnumeration;

typedef struct 
{
    CHAR deviceName[MaxDevName];
    INT32 fd;
    INT32 kmdGroupId;

} HwDevice;

typedef struct
{
    HwDevice requestManager;                                                 //request manger KMD device
    HwDevice CPADevice;                                                             // CPAS KMD device
    HwDevice KMDDevices[128];                                         //Array to hold CSLHw KMD devices
    HwDevice HwSensorSlotDevices;                              //Array to hold CSLHw KMD Sensor slot devices
    INT               fd;
}HWInstance;
HWInstance g_HWinstance;

 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// EnumAndAddHwDevice
///
/// @brief 两个ioctl包装
/// @param  see
///
/// @return None
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Result defaultIoctl(const HwDevice* pDevice, unsigned long request, VOID* pArg);
Result defaultIoctl(INT32 Fd, unsigned long request, VOID* pArg);
 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// EnumAndAddHwDevice
///
/// @brief 具体初始化动作，打开media返回的 注册好的模块/dev/video等等
/// @param  see
///
/// @return None
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL HwAddKMDPrivateDeviceToInstance(const CHAR* deviceName, UINT32 groupId);

 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// EnumAndAddHwDevice
///
/// @brief 打开/dev/media* 查询entity，根据entity type 做ioctl 初始化
///
/// @param  see
///
/// @return None
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Result EnumAndAddHwDevice(
    HwInternalHwEnumeration deviceType,
    UINT32                     deviceClass
);

 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// HWInitiliaze
///
/// @brief 打开/dev/media* 查询entity，根据entity type 做ioctl 初始化
///
/// @param  see
///
/// @return None
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Result HWInitiliaze();
#endif