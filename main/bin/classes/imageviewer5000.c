#include "imageviewer5000.h"
#include "glwrapper.h"
#include "3DMath.h"
#include "TriangleMesh.h"
#include "ColorShader.h"
#include "Assets.h"
#include <android/log.h>
#include <assert.h>

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
	GLuint error = glGetError();
	if (error>0) 
	{
		__android_log_print(ANDROID_LOG_INFO, "NATIVE", "MAKESHADER ERROR %i", error);
		assert(error==0);
	}
	GetTech(techID, Shader);
	error = glGetError();
	if (error>0) 
	{
		__android_log_print(ANDROID_LOG_INFO, "NATIVE", "LOADSHADER ERROR %i", error);
		assert(error==0);
	}
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
	__android_log_print(ANDROID_LOG_INFO, "NATIVE", "copied verts: %i", 
													DragonMesh->numVerts);;
	int i=0;
    for (i=0;i<DragonMesh->numVerts*3;i+=3)
	{
		__android_log_print(ANDROID_LOG_INFO, "NATIVE", "copied verts: %f %f %f", 
												verts[i], verts[i+1], verts[i+2]);
	}

	GLuint error = glGetError();
	if (error>0) 
	{
		__android_log_print(ANDROID_LOG_INFO, "NATIVE", "LOADMESH ERROR %i", error);
		assert(error==0);
	}
}


static void SetupDragonTrans()
{
	static float dt = 0.f;
	dt += 0.01f;
	//Transform meshRotY = RotateY(130);//130
	//Transform meshRotX = RotateX(270.f);//270
	//TransformTrans(&meshRotY, &meshRotX, &Model);
	Vector3 move; move.x = 0.f; move.y = 0.f; move.z = 10.f*sinf(dt);
	Transform moveT = MakeTranslation(&move);
	//TransformTrans(&moveT, &Model, &Model);

	TransformTrans(&ViewProjection, &moveT, &ModelViewProjection);
	//__android_log_print(ANDROID_LOG_INFO, "NATIVE", "Transformed Dragon %f", 5.f*sinf(dt));
}

static void DrawDragon()
{
	glUseProgram(Shader->tech);
    
    GLuint error = glGetError();
	if (error>0) 
	{
		__android_log_print(ANDROID_LOG_INFO, "NATIVE", "USEPROGRAM ERROR %i", error);
		assert(error==0);
	}

	float col[] = {1.f, 0.f, 0.f, 1.f};
	glUniformMatrix4fv(Shader->mvpMatrix, 1, GL_FALSE, 
						(GLfloat*)ModelViewProjection.m);
	glUniform4fv(Shader->color, 1, col);
	glBindBuffer(GL_ARRAY_BUFFER, vb);
	glVertexAttribPointer(Shader->position, 3, GL_FLOAT, GL_FALSE, 12, 0);
	glEnableVertexAttribArray(Shader->position);
	error = glGetError();
	if (error>0) 
	{
		__android_log_print(ANDROID_LOG_INFO, "NATIVE", "DRAWINDEX ERROR %i", error);
		assert(error==0);
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);

	glDrawElements(GL_TRIANGLES, DragonMesh->numTris*3, GL_UNSIGNED_SHORT, 0);
	error = glGetError();
	if (error>0) 
	{
		__android_log_print(ANDROID_LOG_INFO, "NATIVE", "DRAWINDEX ERROR %i", error);
		assert(error==0);
	}	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void on_surface_created()
{
	glClearColor(0.f, 0.f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

 	LoadShader();
	GLuint error = glGetError();
	if (error>0) 
	{
		__android_log_print(ANDROID_LOG_INFO, "NATIVE", "CREATE ERROR %i", error);
		assert(error==0);
	}
	LoadDragon();


	glGenBuffers(1, &vb);
	glBindBuffer(GL_ARRAY_BUFFER, vb);
	glBufferData(GL_ARRAY_BUFFER, DragonMesh->numVerts*4*3, 
						(GLvoid*)verts, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	error = glGetError();
	if (error>0) 
	{
		__android_log_print(ANDROID_LOG_INFO, "NATIVE", "VERTEX ERROR %i", error);
		assert(error==0);
	}	

	glGenBuffers(1, &ib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, DragonMesh->numTris*6,
						(GLvoid*)DragonMesh->vertIndices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	error = glGetError();
	if (error>0) 
	{
		__android_log_print(ANDROID_LOG_INFO, "NATIVE", "INDEX ERROR %i", error);
		assert(error==0);
	}	
}

void on_surface_changed(int width, int height)
{
	glViewport(0, 0, width, height);
	MakePerspectiveTrans(0.f, (float)width/(float)height, 1.f, 10.0f, &Projection);

    GLuint error = glGetError();
	if (error>0) 
	{
		__android_log_print(ANDROID_LOG_INFO, "NATIVE", "GLVIEWPORT ERROR %i", error);
		assert(error==0);
	}

	Vector3 eye; eye.x = 0.f; eye.y = 0.f; eye.z = 0.f;
	Vector3 center; center.x = 0.f; center.y = 0.f; center.z = 0.f;
	Vector3 up; up.x = 0.f; up.y = 1.f; up.z = 0.f;
	MakeLookAtTrans(&eye, &center, &up, &View);
	TransformTrans(&Projection, &View, &ViewProjection);

	error = glGetError();
	if (error>0) 
	{
		__android_log_print(ANDROID_LOG_INFO, "NATIVE", "CHANGED ERROR %i", error);
		assert(error==0);
	}
}

void on_draw_frame()
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	SetupDragonTrans();

	DrawDragon();
}
