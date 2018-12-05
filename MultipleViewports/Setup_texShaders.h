#ifndef SETUP_TEXSHADERS_H
#define SETUP_TEXSHADERS_H

#include "Core.h"

void proInit();
GLuint glCreateProg(string, string, string);
GLuint glCreateShaderStage(const char *, GLenum);
char* glShaderRead(const char *);
void glShaderError(GLuint);
void glUseProgram2(string);

#endif