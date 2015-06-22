#include "Assets.h"

#include <android/log.h>

void GetAsset(char* path, GLchar *text, GLuint *length) 
{
    __android_log_write(ANDROID_LOG_INFO, "NATIVE", "ASSET");
	AAsset* asset = AAssetManager_open(Manager, path, AASSET_MODE_STREAMING);
    __android_log_write(ANDROID_LOG_INFO, "NATIVE", "HAS BEEN");
	*length = AAsset_getLength(asset);
	*text = AAsset_getBuffer(asset);
    __android_log_write(ANDROID_LOG_INFO, "NATIVE", "MANAGED");
}