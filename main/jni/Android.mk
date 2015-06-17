LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := imageviewer5000
LOCAL_CFLAGS    := -Wall -Wextra
LOCAL_SRC_FILES := ../../common/imageviewer5000.c \
                   jni.c \
                   ../../common/3DMath.c \
                   ../../common/TriangleMesh.c \
                   ../../common/ColorShader.c \
                   
LOCAL_LDLIBS := -lGLESv2 -landroid

include $(BUILD_SHARED_LIBRARY)