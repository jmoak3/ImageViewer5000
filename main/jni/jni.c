#include "../../common/imageviewer5000.h"
#include <jni.h>
 
JNIEXPORT void JNICALL Java_com_example_imageviewer5000_ImageViewer5000JNIWrapper_on_1surface_1created
    (JNIEnv * env, jclass cls) {
    on_surface_created();
}
 
JNIEXPORT void JNICALL Java_com_example_imageviewer5000_ImageViewer5000JNIWrapper_on_1surface_1changed
    (JNIEnv * env, jclass cls, jint width, jint height) {
    on_surface_changed();
}
 
JNIEXPORT void JNICALL Java_com_example_imageviewer5000_ImageViewer5000JNIWrapper_on_1draw_1frame
    (JNIEnv * env, jclass cls) {
    on_draw_frame();
}
