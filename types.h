#ifndef TYPES_H
#define TYPES_H

#define TRUE 1;
typedef char CHAR;
typedef bool BOOL;
typedef size_t SIZE_T;
typedef void VOID;
typedef int INT;
typedef uint64_t            UINT64;
typedef int64_t               INT64;
typedef int32_t               INT32;
typedef uint32_t            UINT32;
/*Result Code*/
typedef INT Result;
static const Result ResultSuccess                                      = 0;     //Operation is Successfull
static const Result ResultFailed                          = 1;    //Operation is failed


#endif