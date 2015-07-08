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
		__android_log_print(ANDROID_LOG_INFO, "NATIVE", "GET TECH ERROR %i", error);
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
													DragonMesh->numVerts);
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
	Vector3 move; move.x = 0.f; move.y = 0.f; move.z = 0.f;
	Model = MakeTranslation(&move);
	//TransformTrans(&moveT, &Model, &Model);
	Transform tempTrans;
	TransformTrans(&ViewProjection, &Model, &tempTrans);
	TransposeTrans(&tempTrans, &ModelViewProjection);
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
	glVertexAttribPointer(Shader->position, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(Shader->position);
	error = glGetError();
	if (error>0) 
	{
		__android_log_print(ANDROID_LOG_INFO, "NATIVE", "DRAWVERTEX ERROR %i", error);
		assert(error==0);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	glDrawElements(GL_TRIANGLES, DragonMesh->numInds, GL_UNSIGNED_SHORT, (void*)0);
	error = glGetError();
	if (error>0) 
	{
		__android_log_print(ANDROID_LOG_INFO, "NATIVE", "DRAWINDEX ERROR %i", error);
		assert(error==0);
	}	
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
	glBufferData(GL_ARRAY_BUFFER, DragonMesh->numVerts*sizeof(float)*3, 
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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, DragonMesh->numInds*sizeof(unsigned short),
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
	__android_log_print(ANDROID_LOG_INFO, "NATIVE", "WIDTH HEIGHT %i %i", width, height);
	glViewport(0, 0, width, height);

	GLuint error = glGetError();
	if (error>0) 
	{
		__android_log_print(ANDROID_LOG_INFO, "NATIVE", "GLVIEWPORT ERROR %i", error);
		assert(error==0);
	}

	MakePerspectiveTrans(0.8f, (float)width/(float)height, 1.f, 10.f, &Projection);

   	
	

	error = glGetError();
	if (error>0) 
	{
		__android_log_print(ANDROID_LOG_INFO, "NATIVE", "SURFACECHANGED ERROR %i", error);
		assert(error==0);
	}
}

#define SAMPLES 16
void calcMovingAvg(float* data, float * out)
{
	*out = 0.f;
	int i;
	for (i=0;i<SAMPLES;++i)
	{
		*out += data[i];
	}
	*out /= (float)SAMPLES;
}

void on_draw_frame(float az, float pch, float rll)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	static float yaws[SAMPLES];
	static float pitches[SAMPLES];
	static float rolls[SAMPLES];
	static int index = -1;

	float y,p,r;
	float a=az, b=rll, c=pch;
	if (index<0)
	{
		int i; for (i=0;i<SAMPLES;++i)
		{
			yaws[i] = a;
			pitches[i] = b;
			rolls[i] = c;
		}
		index = 0;
	}
	else
	{
		yaws[index] = a;
		pitches[index] = b;
		rolls[index] = c;
		calcMovingAvg(yaws, &y);
		calcMovingAvg(pitches, &p);
		calcMovingAvg(rolls, &r);
		index = (index+1)%SAMPLES;
	}
	
	Vector3 eye; eye.x = 0.f; eye.y = 0.f; eye.z = -8.f;

	//Transform original = Rotate;

	y = (y - 2.7f);
	p = -(p + 3.14159f);
	r = (r);


	Transform rot;
	Transform yaw = RotateY(y);
	Transform pitch = RotateX(p);
	Transform roll = RotateZ(r);

	//TransformTrans(&pitch, &original, &rot);
	rot = yaw;
	TransformTrans(&pitch, &rot, &rot);
	TransformTrans(&roll, &rot, &rot);

	Vector3 center; center.x = 0.f; center.y = 0.f; center.z = 0.f;
	//Vector3 temp;s
	//SubVec3(&center, &eye, &temp);
	TransformVec3(&rot, &eye, &center);
	//AddVec3(&eye, &eye, &center);

	Vector3 up; up.x = 0.f; up.y = 1.f; up.z = 0.f;
	TransformVec3(&rot, &up, &up);
	NormalizeVec3(&up, &up);

	MakeLookAtTrans(&eye, &center, &up, &View);

	__android_log_print(ANDROID_LOG_INFO, "NATIVE", "Z POSITION %f %f %f", y, p, r);
	__android_log_print(ANDROID_LOG_INFO, "NATIVE", "Z LOOK %f %f %f", center.x, center.y, center.z);
	__android_log_print(ANDROID_LOG_INFO, "NATIVE", "Z UP %f %f %f", up.x, up.y, up.z);

	TransformTrans(&Projection, &View, &ViewProjection);

	SetupDragonTrans();

	DrawDragon();
}
