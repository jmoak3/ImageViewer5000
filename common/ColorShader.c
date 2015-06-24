#include "ColorShader.h"
#include <stdio.h>
#include "Assets.h"
#include <android/log.h>

void GetTech(GLuint tech, ColorShader *shader)
{	
	shader->tech = tech;
	shader->position = glGetAttribLocation(tech, "Positionv4");
	shader->mvpMatrix = glGetAttribLocation(tech, "MVPMatrix4x4");
	shader->color = glGetAttribLocation(tech, "Colorv4");
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
		__android_log_print(ANDROID_LOG_INFO, "NATIVE", "FUCK COMPILE %s", infoLog);
        free(infoLog);
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
		__android_log_print(ANDROID_LOG_INFO, "NATIVE", "FUCK LINK %s", infoLog);
        free(infoLog);
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
	GLchar vertText[4096] = 
    "uniform mat4 MVPMatrix4x4;\n"
    "attribute vec4 Positionv4;\n"
    "void main()\n"
    "{\n"
    "	gl_Position = MVPMatrix4x4 * Positionv4;\n"
	"}";
    GLchar fragText[4096] =
    "precision mediump float;\n"
    "uniform vec4 Colorv4;\n"
    "void main()\n"
    "{\n"
    "	gl_FragColor = Colorv4;\n"
    "}";
	GLuint vertSize = 119, fragSize = 96;

	//GLchar vertText[4096], fragText[4096];
	//GLuint vertSize, fragSize;

    //GetAsset(vFile, &vertText, &vertSize);
    //GetAsset(fFile, &fragText, &fragSize);
	GLuint techID = BuildTech(vertText, vertSize, fragText, fragSize);

	return techID;
}