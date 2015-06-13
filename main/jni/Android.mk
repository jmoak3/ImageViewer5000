LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := imageviewer5000
LOCAL_SRC_FILES := ../../common/imageviewer5000.c jni.c
LOCAL_LDLIBS := -lGLESv2

include $(BUILD_SHARED_LIBRARY)