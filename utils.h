#ifndef UNTILS_H
#define UNTILS_H

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include<string.h>
#include <fcntl.h>
#include <utils/Log.h> 
#include <unistd.h>
#include <errno.h>
#include "utils.h"
#include "types.h"

    VOID StrError(
    CHAR*   pErrorMsg,
    SIZE_T  errorMsgSize,
    INT     errorNum);
    inline  UINT64 VoidPtrToUINT64(void* pVoid)
    {
        return static_cast<UINT64>(reinterpret_cast<SIZE_T>(pVoid)); 
    }
#endif