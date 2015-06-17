#include "ColorShader.h"
#include <stdio.h>

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
	FILE *fp;
	long vertSize;
	char *vertText;

	fp = fopen (vFile, "rb" );
	if( !fp ) perror(vFile),exit(1);

	fseek(fp, 0L, SEEK_END);
	vertSize = ftell(fp);
	rewind(fp);

	vertSize = calloc( 1, vertSize+1 );
	if( !vertSize ) fclose(fp),fputs("memory alloc fails",stderr),exit(1);

	if(1!=fread(vertSize, vertSize, 1, fp))
	  fclose(fp),free(vertSize),fputs("entire read fails",stderr),exit(1);

	fclose(fp);

	long fragSize;
	char *fragText;

	fp = fopen (vFile , "rb" );
	if( !fp ) perror("blah.txt"),exit(1);

	fseek(fp, 0L, SEEK_END);
	fragSize = ftell(fp);
	rewind(fp);

	fragText = calloc(1, fragSize+1);
	if( !fragText ) fclose(fp),fputs("memory alloc fails",stderr),exit(1);

	if(1!=fread(fragText, fragSize, 1, fp))
	  fclose(fp),free(fragText),fputs("entire read fails",stderr),exit(1);

	fclose(fp);

	const GLuint techID = BuildTech(vertText, vertSize, fragText, fragSize);

	free(vertText);
	free(fragText);
	return techID;
}