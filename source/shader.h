#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <GL/glew.h>
#include "ogldev_util.h"

static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
GLuint  CompileShaders(const char *pVSFileName, const char * pFSFileName);

