#ifndef ASSETS_H
#define ASSETS_H

#include <android/asset_manager_jni.h>
#include "glwrapper.h"

void GetAsset(char* path, GLchar *text, GLuint *length);

#endif