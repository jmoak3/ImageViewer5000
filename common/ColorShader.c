#include "ColorShader.h"
#include <stdio.h>
#include "Assets.h"
#include <android/log.h>
#include <assert.h>

void GetTech(GLuint tech, ColorShader *shader)
{	
	shader->tech = tech;
	shader->position = glGetAttribLocation(tech, "Positionv4");

	GLuint error = glGetError();
	if (error>0) 
	{
		__android_log_print(ANDROID_LOG_INFO, "NATIVE", "GET POSITIONSHADER ERROR %i", error);
		assert(error==0);
	}

	shader->mvpMatrix = glGetUniformLocation(tech, "MVPMatrix4x4"); 

	error = glGetError();
	if (error>0)
	{
		__android_log_print(ANDROID_LOG_INFO, "NATIVE", "GET MATRIXSHADER ERROR %i", error);
		assert(error==0);
	}

	shader->color = glGetUniformLocation(tech, "Colorv4");

	error = glGetError();
	if (error>0) 
	{
		__android_log_print(ANDROID_LOG_INFO, "NATIVE", "GET COLORSHADER ERROR %i", error);
		assert(error==0);
	}   
}

GLuint CompileTech(GLenum type, GLchar* source, GLint length) 
{
	GLuint shaderID = glCreateShader(type);
	glShaderSource(shaderID, 1, (const GLchar **)&source, &length);
	glCompileShader(shaderID);

	GLint infoLen = 0;
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLen);
    if(infoLen > 1)
    {
        char* infoLog = malloc(sizeof(char) * infoLen);
    	glGetShaderInfoLog(shaderID, infoLen, NULL, infoLog);
		__android_log_print(ANDROID_LOG_INFO, "NATIVE", "ERROR COMPILE %s", infoLog);
        free(infoLog);
    }
    GLuint error = glGetError();
	if (error>0) 
	{
		__android_log_print(ANDROID_LOG_INFO, "NATIVE", "COMPILER ERROR %i", error);
		assert(error==0);
	}

	return shaderID;
}

GLuint LinkTech(GLuint vertexshader, GLuint fragshader) 
{
	GLuint techID = glCreateProgram();

	glAttachShader(techID, vertexshader);
	glAttachShader(techID, fragshader);
	glLinkProgram(techID);

	GLuint linked = 1;
	glGetProgramiv(techID, GL_LINK_STATUS, &linked);
	GLint infoLen = 0;
	glGetProgramiv(techID, GL_INFO_LOG_LENGTH, &infoLen);
    if(!linked && infoLen > 1)
    {
        char* infoLog = malloc(sizeof(char) * infoLen);
  		glGetProgramInfoLog(techID, infoLen, NULL, infoLog);
		__android_log_print(ANDROID_LOG_INFO, "NATIVE", "ERROR LINK %s", infoLog);
        free(infoLog);
    } 
    GLuint error = glGetError();
	if (error>0) 
	{
		__android_log_print(ANDROID_LOG_INFO, "NATIVE", "LINKER ERROR %i", error);
		assert(error==0);
	}

	return techID;
}

GLuint BuildTech(GLchar * vert, GLint vertLength, GLchar * frag, GLint fragLength) 
{
	GLuint vertexshader = CompileTech(GL_VERTEX_SHADER, vert, vertLength);
	GLuint fragshader = CompileTech(GL_FRAGMENT_SHADER, frag, fragLength);
	return LinkTech(vertexshader, fragshader);
}

GLuint MakeShader(GLchar * vFile, GLchar * fFile)
{
	GLchar vertText[4096], fragText[4096];
	GLuint vertSize, fragSize;

    GetAsset(vFile, &vertText, &vertSize);
    GetAsset(fFile, &fragText, &fragSize);
	__android_log_print(ANDROID_LOG_INFO, "NATIVE", "SHADER %s", vertText);
	__android_log_print(ANDROID_LOG_INFO, "NATIVE", "SHADER %s", fragText);
	GLuint techID = BuildTech(vertText, vertSize, fragText, fragSize);

	return techID;
}