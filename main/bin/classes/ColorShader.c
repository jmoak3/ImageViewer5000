#include "ColorShader.h"
#include <stdio.h>
#include "Assets.h"
#include <android/log.h>

void GetTech(GLuint tech, ColorShader *shader)
{	
	shader->tech = tech;
	shader->position = glGetAttribLocation(tech, "Position");
	shader->mvpMatrix = glGetAttribLocation(tech, "MVPMatrix");
	shader->color = glGetAttribLocation(tech, "Color");
}

GLuint CompileTech(GLenum type, GLchar* source, GLint length) 
{
	GLuint shaderID = glCreateShader(type);
	glShaderSource(shaderID, 1, (const GLchar **)&source, &length);
	glCompileShader(shaderID);
	return shaderID;
}

GLuint LinkTech(GLuint vertexshader, GLuint fragshader) 
{
	GLuint techID = glCreateProgram();

	glAttachShader(techID, vertexshader);
	glAttachShader(techID, fragshader);
	glLinkProgram(techID);
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
/*
	GLchar vertText[4096] = 
    "uniform mat4 MVPMatrix;\nattribute vec4 Position;\nvoid main()\n{\n    gl_Position = MVPMatrix * Position;\n}";
    GLchar fragText[4096] =
    "precision mediump float;\nuniform vec4 Color;\nvoid main()\n{    gl_FragColor = Color;\n}";
	GLuint vertSize = 103, fragSize = 85;
*/
	GLchar vertText[4096], fragText[4096];
	GLuint vertSize, fragSize;

    GetAsset(vFile, &vertText, &vertSize);
    GetAsset(fFile, &fragText, &fragSize);
	GLuint techID = BuildTech(vertText, vertSize, fragText, fragSize);

	return techID;
}