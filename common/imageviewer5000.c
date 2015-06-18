#include "imageviewer5000.h"
#include "glwrapper.h"
#include "3DMath.h"
#include "TriangleMesh.h"
#include "ColorShader.h"

#include <android/log.h>

static Transform Model;
static Transform View;
static Transform Projection;
static Transform ViewProjection;
static Transform ModelViewProjection;
static TriangleMesh* DragonMesh;
static Triangle* DragonTris;

static ColorShader* Shader;

static void LoadShader()
{
    __android_log_write(ANDROID_LOG_INFO, "NATIVE", "HIII!!");
	GLuint techID = MakeShader("content/shader.vsh", "content/shader.fsh");
	GetTech(techID, Shader);
    __android_log_write(ANDROID_LOG_INFO, "NATIVE", "BIEE!!");
}


//USE ASSET MANAGER TO INCLUDE THINGS IN ASSETS FOLDER!!
/*#include "platform_asset_utils.h"
#include "macros.h"
#include "platform_log.h"
#include <android/asset_manager_jni.h>
#include <assert.h>

static AAssetManager* asset_manager;

JNIEXPORT void JNICALL Java_com_learnopengles_airhockey_platform_PlatformFileUtils_init_1asset_1manager(JNIEnv * env, jclass jclazz, jobject java_asset_manager) {
	UNUSED(jclazz);
	asset_manager = AAssetManager_fromJava(env, java_asset_manager);
}

FileData get_asset_data(const char* relative_path) {
	assert(relative_path != NULL);
	AAsset* asset = AAssetManager_open(asset_manager, relative_path, AASSET_MODE_STREAMING);
	assert(asset != NULL);

	return (FileData) { AAsset_getLength(asset), AAsset_getBuffer(asset), asset };
}

void release_asset_data(const FileData* file_data) {
	assert(file_data != NULL);
	assert(file_data->file_handle != NULL);
	AAsset_close((AAsset*)file_data->file_handle);
}

*/

static void LoadDragon()
{
    __android_log_write(ANDROID_LOG_INFO, "NATIVE", "B22I222EE!!");
	Vector3 o; o.x = 0.f; o.y = 0.f; o.z = 0.f;
	Transform or = MakeTranslation(&o);

	//Initializemesh
	DragonMesh = malloc(sizeof(TriangleMesh));
	Material mat; mat.red = 255.f; mat.green = 0.f; mat.blue = 0.f; mat.filler = 0.f;
    __android_log_write(ANDROID_LOG_INFO, "NATIVE", "9999");
	FormTriangleMesh("content/sphere.obj", DragonMesh, &or, &mat);
    __android_log_write(ANDROID_LOG_INFO, "NATIVE", "451342!!");
}

static void SetupDragonTrans()
{
	Transform meshRotY = RotateY(130);//130
	Transform meshRotX = RotateX(270.f);//270
	TransformTrans(&meshRotY, &meshRotX, &Model);
	Vector3 move; move.x = 0.f; move.y = 0.f; move.z = 0.f;
	Transform moveT = MakeTranslation(&move);
	TransformTrans(&moveT, &Model, &Model);

	TransformTrans(&ViewProjection, &Model, &ModelViewProjection);
}

static void DrawDragon()
{
	glUseProgram(Shader->tech);

	glUniformMatrix4fv(Shader->mvpMatrix, 1, GL_FALSE, (GLfloat*)ModelViewProjection.m);
	glUniform4fv(Shader->color, 1, &DragonMesh->material.red);

	glBindBuffer(GL_ARRAY_BUFFER, *(DragonMesh->vertIndices));
	glVertexAttribPointer(Shader->position, 3, GL_FLOAT,
					      GL_FALSE, 0, (GLvoid*)DragonMesh->vertPoints);
	glEnableVertexAttribArray(Shader->position);

	glDrawArrays(GL_TRIANGLES, 0, DragonMesh->numTris*3);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void on_surface_created()
{
	glClearColor(0.f, 0.f, 1.0f, 0.0f);

	LoadDragon();
	LoadShader();
}

void on_surface_changed(int width, int height)
{
	glViewport(0, 0, width, height);
	MakePerspectiveTrans(45, (float)width/(float)height, 1.0f, 10.0f, &Projection);

	Vector3 eye; eye.x = 0.f; eye.y = 1.f; eye.z = 1.f;
	Vector3 center; center.x = 0.f; center.y = 0.f; center.z = 0.f;
	Vector3 up; up.x = 0.f; up.y = 1.f; up.z = 0.f;
	MakeLookAtTrans(&eye, &center, &up, &View);
}

void on_draw_frame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	TransformTrans(&Projection, &View, &ViewProjection);
	SetupDragonTrans();
	DrawDragon();
}
