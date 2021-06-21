#include "utils.h"

VOID StrError(
    CHAR*   pErrorMsg,
    SIZE_T  errorMsgSize,
    INT     errorNum)
{
    (void)strlcpy(pErrorMsg, strerror(errorNum), errorMsgSize);
}

