#ifndef ASSETS_H
#define ASSETS_H

#include <android/asset_manager_jni.h>
#include "glwrapper.h"

static AAssetManager* AssetManager;

//Link to the java call initializing the asset manager, this is for opening the mesh/shader files in assets.
JNIEXPORT void JNICALL Java_com_example_imageviewer5000_ImageViewer5000Renderer_initialize_1asset_1manager(JNIEnv * env, jclass jclazz, jobject java_asset_manager) 
{
	AssetManager = AAssetManager_fromJava(env, java_asset_manager);
}

void GetAsset(char* path, GLchar *text, GLuint *length) 
{
	AAsset* asset = AAssetManager_open(AssetManager, path, AASSET_MODE_STREAMING);

	*length = AAsset_getLength(asset);
	*text = AAsset_getBuffer(asset);
}

#endif