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
    v4l2_capability caps;
    {
        Result ret = ioctl (mDeviceFd, VIDIOC_QUERYCAP, &caps);
        if (ret < 0)
        {
            CHAR errnoStr[100] = {0};
            StrError(errnoStr, sizeof(errnoStr), errno);
            LOGE("fail to get device capabilitys  for  %s Fd = %d %s", pDeviceName, mDeviceFd, errnoStr);
            return ResultFailed;
        }
    }

    //Report Device capbilitys
    LOGI("Open Device %s  Fd = %d", pDeviceName, mDeviceFd );
    LOGI("Driver %s", caps.driver);
    LOGI("Card %s", caps.card);
    LOGI("Version:%d.%d.%d", ((caps.version >> 16) & 0xFF), ((caps.version >> 8) & 0xFF), ((caps.version) & 0xFF));
    LOGI("All Caps %x", caps.capabilities);
    LOGI("Device Caps %x", caps.device_caps);

    //Enumerate the available capture formats (if any)
    v4l2_fmtdesc formatDescriptions;
    formatDescriptions.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    for (int i = 0; 1; i++)
    {
        formatDescriptions.index = i;
        if (ioctl (mDeviceFd, VIDIOC_ENUM_FMT, &formatDescriptions) == 0)
        {
            LOGI("%s. :%u  flag:%x", formatDescriptions.description, formatDescriptions.pixelformat, formatDescriptions.flags);
        }
        else
        {
            //Have no size
            break;
        }
    }

    // Verify we can use this device for video capture
    if (!(caps.capabilities & V4L2_CAP_VIDEO_CAPTURE) || !( caps.capabilities & V4L2_CAP_STREAMING))
    {
        LOGE("Cpas %0x is not a video capture", caps.capabilities);
        return ResultFailed;
    }

    //set property format
    v4l2_format format;
    format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    format.fmt.pix.pixelformat = V4L2_PIX_FMT_NV12;
    format.fmt.pix.width = mwidth;
    format.fmt.pix.height = mheight;
    LOGI("Requst Info: %c %c %c %c (%x)",((char*)&format.fmt.pix.pixelformat)[0], ((char*)&format.fmt.pix.pixelformat)[1],((char*)&format.fmt.pix.pixelformat)[2], ((char*)&format.fmt.pix.pixelformat)[3],format.fmt.pix.pixelformat);
    
    if (ioctl(mDeviceFd, VIDIOC_S_FMT, &format) < 0)
    {
        LOGE("VIDIOC_S_FMT failed");
        return ResultFailed;
    }

    //Report current format

    return ResultSuccess;
}

INT main()
{
    VideoCapture video;
    video.DefaultOpen("/dev/video0",  O_RDWR | O_NONBLOCK);

    return ResultSuccess;
}

