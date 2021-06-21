ifeq ($(CAMX_CHICDK_PATH),)
LOCAL_PATH := $(abspath $(call my-dir)/../..)
CAMX_CHICDK_PATH := $(abspath $(LOCAL_PATH)/../../../..)
else
LOCAL_PATH := $(CAMX_CHICDK_PATH)/oem/qcom/node/v4l2
endif

include $(CLEAR_VARS)

# Module supports function call tracing via ENABLE_FUNCTION_CALL_TRACE
# Required before including common.mk
SUPPORT_FUNCTION_CALL_TRACE := 1

# Get definitions common to the CAMX project here
include $(CAMX_CHICDK_PATH)/core/build/android/common.mk

LOCAL_INC_FILES :=              \
    Hwinternel.h                    \
    types.h                                     \
    utils.h

LOCAL_SRC_FILES :=              \
    Hwinternel.cpp                \
    utils.cpp

LOCAL_C_LIBS := $(CAMX_C_LIBS)

LOCAL_C_INCLUDES :=               \
    $(CAMX_C_INCLUDES)            \
    $(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/usr/include             \
    $(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/usr/camera/include/uapi

# Compiler flags
LOCAL_CFLAGS := $(CAMX_CFLAGS)
LOCAL_CPPFLAGS := $(CAMX_CPPFLAGS)


LOCAL_MODULE := VideoCapture

LOCAL_MODULE_RELATIVE_PATH := $(CAMX_LIB_OUTPUT_PATH)

include $(BUILD_EXECUTABLE)
