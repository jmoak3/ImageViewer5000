#include "../../common/imageviewer5000.h"
#include "../../common/Assets.h"
#include <jni.h>

#include <android/log.h>

JNIEXPORT void JNICALL Java_com_example_imageviewer5000_ImageViewer5000Renderer_on_1surface_1created
    (JNIEnv * env, jclass cls) {
    on_surface_created();
}
 
JNIEXPORT void JNICALL Java_com_example_imageviewer5000_ImageViewer5000Renderer_on_1surface_1changed
    (JNIEnv * env, jclass cls, jint width, jint height) {
    on_surface_changed(width, height);
}
 
JNIEXPORT void JNICALL Java_com_example_imageviewer5000_ImageViewer5000Renderer_on_1draw_1frame
    (JNIEnv * env, jclass cls) {
    on_draw_frame();
}

//Link to the java call initializing the asset manager, this is for opening the mesh/shader files in assets.
JNIEXPORT void JNICALL Java_com_example_imageviewer5000_ImageViewer5000Renderer_init_1asset_1manager(JNIEnv * env, jclass jclazz, jobject java_asset_manager)
{
	Manager = AAssetManager_fromJava(env, java_asset_manager);
}

void GetAsset(char* path, GLchar *text, GLuint *length)
{
	AAsset* asset = AAssetManager_open(Manager, path, AASSET_MODE_STREAMING);
	*length = AAsset_getLength(asset);
	*text = AAsset_getBuffer(asset);
}
