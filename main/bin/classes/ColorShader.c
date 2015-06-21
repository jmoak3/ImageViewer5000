#include "ColorShader.h"
#include <stdio.h>
#include "Assets.h"


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
	GLint ignore;
	glShaderSource(shaderID, 1, (const GLchar **)&source, &length);
	glCompileShader(shaderID);
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &ignore);

	return shaderID;
}

GLuint LinkTech(GLuint vertexshader, GLuint fragshader) 
{
	GLuint techID = glCreateProgram();
	GLint ignore;

	glAttachShader(techID, vertexshader);
	glAttachShader(techID, fragshader);
	glLinkProgram(techID);
	glGetProgramiv(techID, GL_LINK_STATUS, &ignore);

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
	GLchar vertText, fragText;
	GLuint vertSize, fragSize;
    GetAsset(vFile, &vertText, &vertSize);
    GetAsset(vFile, &vertText, &vertSize);
	const GLuint techID = BuildTech(vertText, vertSize, fragText, fragSize);

	return techID;
}