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
static float* verts;
static ColorShader* Shader;
static GLuint vb, ib;

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
	Material mat; mat.red = 1.f; mat.green = 1.f; mat.blue = 1.f;// mat.filler = 1.f;
	FormTriangleMesh("content/sphere.obj", DragonMesh, &or, &mat);

	verts = MoveVec3sToFloatsArray(DragonMesh->vertPoints, DragonMesh->numVerts);
}


static void SetupDragonTrans()
{
	static float dt = 0.f;
	dt += 0.01f;
	//Transform meshRotY = RotateY(130);//130
	//Transform meshRotX = RotateX(270.f);//270
	//TransformTrans(&meshRotY, &meshRotX, &Model);
	Vector3 move; move.x = 0.f; move.y = 0.f; move.z = 5.f*sinf(dt);
	Transform moveT = MakeTranslation(&move);
	TransformTrans(&moveT, &Model, &Model);

	TransformTrans(&ViewProjection, &moveT, &ModelViewProjection);
	//__android_log_print(ANDROID_LOG_INFO, "NATIVE", "Transformed Dragon %f", 5.f*sinf(dt));
}

static void DrawDragon()
{
	glUseProgram(Shader->tech);
    
    float col[] = {1.f, 0.f, 0.f, 1.0f};
	glUniformMatrix4fv(Shader->mvpMatrix, 1, GL_FALSE, 
						(GLfloat*)ModelViewProjection.m);
	glUniform4fv(Shader->color, 1, col);
    
    glBindBuffer(GL_ARRAY_BUFFER, vb);

	glVertexAttribPointer(Shader->position, 3, GL_FLOAT, GL_FALSE, 12, 0);
	glEnableVertexAttribArray(Shader->position);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);

    glDrawElements(GL_TRIANGLES, DragonMesh->numTris*3, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void on_surface_created()
{
	glClearColor(0.f, 0.f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);

 	LoadShader();
	LoadDragon();

	glGenBuffers(1, &vb);
	glBindBuffer(GL_ARRAY_BUFFER, vb);
    glBufferData(GL_ARRAY_BUFFER, DragonMesh->numVerts*12, 
    					(GLvoid*)verts, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &ib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, DragonMesh->numTris*6,
    					(GLvoid*)DragonMesh->vertIndices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void on_surface_changed(int width, int height)
{
	glViewport(0, 0, width, height);
	MakePerspectiveTrans(60, (float)width/(float)height, 1.f, 10.0f, &Projection);

	Vector3 eye; eye.x = 1.5f; eye.y = 1.f; eye.z = 2.f;
	Vector3 center; center.x = 0.f; center.y = 0.f; center.z = 0.f;
	Vector3 up; up.x = 0.f; up.y = 1.f; up.z = 0.f;
	MakeLookAtTrans(&eye, &center, &up, &View);
	TransformTrans(&Projection, &View, &ViewProjection);
}

void on_draw_frame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SetupDragonTrans();
	DrawDragon();
}
