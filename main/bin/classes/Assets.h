#ifndef ASSETS_H
#define ASSETS_H

#include <android/asset_manager_jni.h>
#include "glwrapper.h"

static AAssetManager* Manager;

void GetAsset(char* path, GLchar *text, GLuint *length);

#endif