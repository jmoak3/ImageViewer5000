#include "imageviewer5000.h"
#include "glwrapper.h"
#include "3DMath.h"
#include "TriangleMesh.h"
#include "ColorShader.h"
#include "Assets.h"
#include <android/log.h>

static Transform Model;
static Transform View;
static Transform Projection;
static Transform ViewProjection;
static Transform ModelViewProjection;
static TriangleMesh* DragonMesh;

static ColorShader* Shader;

static void LoadShader()
{
	GLuint techID = MakeShader("content/shader.vsh", "content/shader.fsh");
	Shader = malloc(sizeof(ColorShader));
	GetTech(techID, Shader);
}

static void LoadDragon()
{
	Vector3 o; o.x = 0.f; o.y = 0.f; o.z = 0.f;
	Transform or = MakeTranslation(&o);

	//Initializemesh
	DragonMesh = malloc(sizeof(TriangleMesh));
	Material mat; mat.red = 1.f; mat.green = 0.f; mat.blue = 0.f; mat.filler = 0.f;
	FormTriangleMesh("content/sphere.obj", DragonMesh, &or, &mat);
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
	glClearColor(0.f, 0.f, 0.0f, 0.0f);

	LoadShader();
	LoadDragon();
}

void on_surface_changed(int width, int height)
{
	glViewport(0, 0, width, height);
	MakePerspectiveTrans(45, (float)width/(float)height, 0.1f, 1.0f, &Projection);

	Vector3 eye; eye.x = 0.f; eye.y = 0.5f; eye.z = 0.5f;
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
