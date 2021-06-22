////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016-2019 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file  debug.h
/// @brief Debug related defines
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef DEBUG_H
#define DEBUG_H

// Debug options globally controlled by the DEBUG symbol
#if DEBUG

#define ASSERTS_ENABLED            1
#define CONTINGENCY_INDUCER_ENABLE 1
#define USE_MEMSPY                 0
#define SETTINGS_DUMP_ENABLE            1
#define DETECT_WRITE_TO_FREED_MEM  1 // see below, requires memspy to be set to 1

/// @todo (-560): Add setting to enable/disable Freed-Write detection
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DETECT_WRITE_TO_FREED_MEM: Detect writes to freed allocations feature
//
// Useful for debugging writes to stale pointers.
//
// NOTE: This works by setting freed buffers to read-only in the page table instead of freeing them. There are a few
//       implications:
//
//       1) Catching a write to a freed portion of memory will manifest as an access violation.
//       2) This feature intentionally causes memory leaks by not freeing the allocations.
//       3) This feature allocates more memory since each allocation must be aligned to page(s).
//
//       This could be improved by adding windows support (linux only at the moment) and a garbage collector for
//       the leaked memory.
//
//       Requires USE_MEMSPY to be enabled.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // DEBUG

// NOWHINE GR017 : Using built in so we don't need any includes
typedef unsigned int Assert;
static const Assert AssertConditional    = (1 << 0);    ///< A typical conditional assert, e.g. ASSERT(val != 4);
static const Assert AssertAlways         = (1 << 1);    ///< ASSERT_ALWAYS()
static const Assert AssertNotImplemented = (1 << 2);    ///< NOT_IMPLEMENTED()
static const Assert AssertNotTested      = (1 << 3);    ///< NOT_TESTED()


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Global for debug log settings
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// AssertTypeToString
///
/// @brief  Converts an AssertType into a human readable string
///
/// @param  assertType AssertType to convert to a string
///
/// @return Stringized AssertType
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NOWHINE GR017 : Using built in so we don't need any includes
const char* AssertTypeToString(
    Assert assertType);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// UpdateAssertMask
///
/// @brief  Updates assert behavior
///
/// @param  assertMask Mask of AssertTypes to throw asserts for
///
/// @return None
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UpdateAssertMask(
    Assert assertMask);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// FireAssert
///
/// @brief  Runtime asserts if enabled for this assert type
///
/// @param  assertType   Assert type
///
/// @return None
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FireAssert(
    Assert assertType);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// LogAssert
///
/// @brief Logs the asserts with the optional message
///
/// @param  assertType   Assert type
/// @param  pFileName    file name that triggered the assert
/// @oaram  line         line number that triggered the assert
/// @oaram  pFunction    function that triggered the assert
/// @oaram  pCondition   condition that triggered assert
/// @oaram  ...          arg list
///
/// @return None
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NOWHINE GR017 : Using built in so we don't need any includes
void LogAssert(unsigned int assertType,
    const char* pFileName, unsigned int line, const char* pFunction, const char* pCondition, ...); // NOWHINE GR017 <-

#if (ASSERTS_ENABLED)
// Common function for logging asserts. Use the macros below instead
#define ASSERT_EX(t, c, ...) LogAssert((t), __FILE__, __LINE__, __FUNCTION__, (c), ##__VA_ARGS__)
#else // ASSERTS_ENABLED
#define ASSERT_EX(type, fmt, ...)      void(0)
#endif // ASSERTS_ENABLED

// NOWHINE CP049: We're defining STATIC_ASSERT here
#define STATIC_ASSERT(condition)                    static_assert(condition, #condition)

// NOWHINE CP049: We're defining STATIC_ASSERT here
#define STATIC_ASSERT_MESSAGE(condition, message)   static_assert(condition, message)

#define ASSERT(condition) do                                                                  \
                               {                                                                   \
                                   if (!(condition))                                               \
                                   {                                                               \
                                       ASSERT_EX(AssertConditional, #condition);          \
                                   }                                                               \
                               } while ((void)0, 0)                                                \

#define ASSERT_MESSAGE(condition, fmt, ...) do                                                \
                                                 {                                                 \
                                                     if (!(condition))                             \
                                                     {                                             \
                                                        ASSERT_EX(AssertConditional,      \
                                                                       (fmt), ##__VA_ARGS__);      \
                                                      }                                            \
                                                 } while ((void)0, 0)                              \


#define ASSERT_ALWAYS()                    ASSERT_EX(AssertAlways,          "ALWAYS")
#define ASSERT_ALWAYS_MESSAGE(fmt, ...)    ASSERT_EX(AssertAlways,          fmt, ##__VA_ARGS__)
#define NOT_IMPLEMENTED()                  ASSERT_EX(AssertNotImplemented,  "NOT IMPLEMENTED")
#define NOT_TESTED()                       ASSERT_EX(AssertNotTested,       "NOT TESTED")

#endif // DEBUG_H
