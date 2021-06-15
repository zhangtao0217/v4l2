#ifndef VIDEO_CAPTURE_H
#define VIDEO_CAPTURE_H
#include <linux/videodev2.h>
#include "types.h"

class VideoCapture
{
    public:
    BOOL DefaultOpen(
        const CHAR* pDeviceName,
        INT flags
    );
    private:
    INT mDeviceFd = -1;
    INT mwidth = 1920;
    INT mheight = 1080;
};
#endif