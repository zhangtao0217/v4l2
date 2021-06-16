#include <media/cam_defs.h>
#include <media/cam_sensor.h>
#include<stdlib.h>
#include "VideoCapture.h"
#include "utils.h"
#include "logger.h"


BOOL VideoCapture::DefaultOpen(
    const char* pDeviceName,
    INT flags)
{
    INT fd = -1;

    if(pDeviceName != NULL)
    {
        //open Device /dev/video0
        mDeviceFd = open(pDeviceName, flags);
        if (mDeviceFd <  0)
        {
            CHAR errnoStr[100] = {0};
            StrError(errnoStr, sizeof(errnoStr), errno);
            LOGI("fail to opend device %s, %s", pDeviceName,  errnoStr);
            return ResultFailed;
        }
    }
    
    //query v4l2 device capability
    cam_control ioctlCmd;
    VOID* KMDDeviceData = static_cast<cam_sensor_query_cap *>(calloc(1, sizeof( cam_sensor_query_cap)));
    ioctlCmd.op_code = CAM_QUERY_CAP;
    ioctlCmd.size = sizeof(cam_sensor_query_cap);
    ioctlCmd.handle_type = CAM_HANDLE_USER_POINTER;
    ioctlCmd.reserved = 0;
    ioctlCmd.handle = VoidPtrToUINT64(KMDDeviceData);
    
    Result ret = ioctl (mDeviceFd, VIDIOC_CAM_CONTROL, &KMDDeviceData);
    if (ret < 0)
    {
        CHAR errnoStr[100] = {0};
        StrError(errnoStr, sizeof(errnoStr), errno);
        LOGE("tzhang fail to get device capabilitys  for  %s Fd = %d %s", pDeviceName, mDeviceFd, errnoStr);
        return ResultFailed;
    }
    return ResultSuccess;
}

INT main()
{
    VideoCapture video;
    video.DefaultOpen("/dev/video0",  O_RDWR | O_NONBLOCK);

    return ResultSuccess;
}

