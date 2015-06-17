#ifndef COLORSHADER_H
#define COLORSHADER_H

#include "glwrapper.h"

typedef struct 
{
	GLuint tech;
	GLint position;
	GLint mvpMatrix;
	GLint color;
} ColorShader;

void GetTech(GLuint tech, ColorShader *shader);

GLuint CompileTech(GLenum type, GLchar* source, GLint length);
GLuint LinkTech(GLuint vertexshader, GLuint fragshader);
GLuint BuildTech(GLchar * vert, GLint vertLength, GLchar * frag, GLint fragLength);
GLuint MakeShader(GLchar * vFile, GLchar * fFile);

#endif