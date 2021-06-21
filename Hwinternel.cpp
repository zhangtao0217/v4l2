#include <linux/media.h>
#include<stdlib.h>
 #include <unistd.h>
#include "Hwinternel.h"
#include "utils.h"
#include "logger.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// defaultIoctl
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Result defaultIoctl(const HwDevice* pDevice, unsigned long request, VOID* pArg)
{
    INT returnCode = -1;
    Result res = ResultFailed;

    returnCode = ioctl (pDevice->fd, request, pArg);
    if (returnCode < 0)
    {
            CHAR errnoStr[100] = {0};
            StrError(errnoStr, sizeof(errnoStr), errno);
            LOGE("fail to opend device %s  fd = %d, %s",pDevice->deviceName, pDevice->fd, errnoStr);
    }
    return returnCode;
}
Result defaultOpen(const CHAR* deviceName, INT flags)
{
    INT fd = -1;
    fd = open(deviceName, flags);
    if (fd < 0)
    {
        CHAR errnoStr[100] = {0};
        StrError(errnoStr, sizeof(errnoStr), errno);
        LOGE("fail to open device %s reason %s", deviceName, errnoStr);
    }
    return fd;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// defaultIoctl
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Result defaultIoctl(INT32 Fd, unsigned long request, VOID* pArg)
{
    INT returnCode = -1;
    Result res = ResultFailed;
    INT pollCount = 1;

    returnCode = ioctl (Fd, request, pArg);
    if (returnCode < 0)
    {
            CHAR errnoStr[100] = {0};
            StrError(errnoStr, sizeof(errnoStr), errno);
            LOGE("fail   fd = %d, %s", Fd, errnoStr);
    }
    return returnCode;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// HwAddKMDPrivateDeviceToInstance
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HwAddKMDPrivateDeviceToInstance(const CHAR* deviceName, UINT32 groupId)
{
    INT fd = -1;
    Result res = ResultFailed;

    fd = defaultOpen(deviceName, O_RDWR | O_NONBLOCK);
    if (fd < 0)

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// EnumAndAddHwDevice
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Result EnumAndAddHwDevice(
    HwInternalHwEnumeration deviceType, 
    UINT32                     deviceClass)
{
    INT32 mediaFd  = 0;
    Result res = 0;
    CHAR mediaName[MaxDevName];
    struct media_device_info mediadevInfo;
    BOOL returnCode = 0;
    INT32 numberMediaDevice = 0;
    INT32 numEntities =0;

    
    while (1)
    {   
        SNPrintF(mediaName, sizeof(mediaName), "/dev/media%d", numberMediaDevice);
        
        mediaFd = open(mediaName, O_RDWR | O_NONBLOCK);
        //open Device /dev/video0
        if (mediaFd <  0)
        {
            CHAR errnoStr[100] = {0};
            StrError(errnoStr, sizeof(errnoStr), errno);
            LOGE("fail to opend device %s media fd = %d, %s", mediaName, mediaFd, errnoStr);
            break;
        }
        res = defaultIoctl(mediaFd, MEDIA_IOC_DEVICE_INFO, &mediadevInfo );
        if (res != ResultSuccess)
        {
            LOGE("fail to get device info %s", mediaName);
        }
        
        if (0 != (strncmp(mediadevInfo.model, CAM_REQ_MGR_VNODE_NAME, sizeof(mediadevInfo.model))))
        {
            close(mediaFd);
            continue;
        }
        numberMediaDevice = 1;
        while (1)
        {
             struct media_entity_desc entity = {};
             CHAR deviceName[MaxDevName] = {0};
             CHAR subDeviceName[MaxDevName] = {0};

            entity.id = numberMediaDevice;
            res = defaultIoctl(mediaFd, MEDIA_IOC_ENUM_ENTITIES, &entity);
            if (res != ResultSuccess)
            {
                LOGE("fail to enum entities for %s(%d)", entity.name, entity.id);
                break;
            }
             numEntities = entity.id | MEDIA_ENT_ID_FLAG_NEXT;
            //  LOGI("Found entity names %s type %d id %d device_class %d device_type %d", 
            //                 entity.name, entity.id,deviceClass, deviceType);
             LOGE("Found entity names %s  id %d", entity.name, entity.id);
             
             if (entity.type == deviceClass)
             {
                 LOGI("it is video type name %s", entity.name);
                 SNPrintF(deviceName, sizeof(deviceName), "/dev/%s", entity.name);
                 
             }
        }

    }
    return ResultSuccess;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// HWInitiliaze
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Result HWInitiliaze()
{
    Result res = 0;
    if (EnumAndAddHwDevice(InternalHwVideodevice, CAM_VNODE_DEVICE_TYPE))
    {
        LOGE("right?");
    }
    else
    {
        LOGE("fail to aquire CPAS");
    }
    return res;
}
INT32 main()
{
    HWInitiliaze();
    return ResultSuccess;
}

