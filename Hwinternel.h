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


// @brief CSLHw KMD device classifications.
typedef enum
{
    InternalHwVideodevice = 0,     ///< This CSLHw KMD device of type v4l video device
    InternalHwVideoSubdevice,      ///< This CSLHw KMD device of type v4l subdev device
    InternalHwVideoSubdeviceAll,   ///< This CSLHw KMD device of type v4l all subdev devices
    InternalHwVideoInvalid         ///< This is upper bound check value
} HwInternalHwEnumeration;

static const INT   MaxDevName              = 64;  ///< Max size of a KMD device name


typedef struct 
{
    CHAR deviceName[MaxDevName];
    INT32 fd;

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


Result defaultIoctl(const HwDevice* pDevice, unsigned long request, VOID* pArg);
Result defaultIoctl(INT32 Fd, unsigned long request, VOID* pArg);
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