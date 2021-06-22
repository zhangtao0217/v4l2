#include "utils.h"

VOID StrError(
    CHAR*   pErrorMsg,
    SIZE_T  errorMsgSize,
    INT     errorNum)
{
    (void)strlcpy(pErrorMsg, strerror(errorNum), errorMsgSize);
}


// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // Mutex class
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // Mutex::Create
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Mutex* Mutex::Create(
//     const CHAR* pResourceName)
// {
//     Mutex* pMutex = NULL;

//     pMutex = NEW Mutex();
//     if (NULL != pMutex)
//     {
//         if (ResultSuccess != pMutex->Initialize(pResourceName))
//         {
//             DELETE pMutex;
//             pMutex = NULL;
//         }
//     }

//     return pMutex;
// }
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // Mutex::Initialize
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CamxResult Mutex::Initialize(
//     const CHAR* pResourceName)
// {
//     Result          result      = ResultSuccess;
//     pthread_mutexattr_t attr;
//     BOOL                bValidAttr  = FALSE;      // TRUE once attr has been initialized

//     ASSERT(pResourceName != NULL);

//     OsUtils::StrLCpy(m_pResourceName, pResourceName, MaxResourceNameSize);

//     if (pthread_mutexattr_init(&attr) == 0)
//     {
//         bValidAttr = TRUE;
//     }
//     else
//     {
//         result = CamxResultEFailed;
//     }

//     // Using re-entrant mutexes
//     if ((CamxResultSuccess == result) &&
//         (pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP) != 0))
//     {
//         result = CamxResultEFailed;
//     }

//     if ((CamxResultSuccess == result) &&
//         (pthread_mutex_init(&m_mutex, &attr) == 0))
//     {
//         CAMX_TRACE_MESSAGE_F(CamxLogGroupSync, "Mutex Init");
//         m_validMutex = TRUE;
//     }
//     else
//     {
//         result = CamxResultEFailed;
//     }

//     if (TRUE == bValidAttr)
//     {
//         pthread_mutexattr_destroy(&attr);
//     }

//     return result;
// }