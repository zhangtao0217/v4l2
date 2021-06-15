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
#endif