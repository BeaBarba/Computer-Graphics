#pragma once

#include "lib.h"
#include "StbImage.h"
#include <time.h>

class ShaderMaker
{
public:
	static GLuint createProgram(char* vertexfilename, char* fragmentfilename);
	static char* readShaderSource(const char* shaderFile);
	static GLuint initShader(char* vertexShader, char* fragmentShader);

private:
	ShaderMaker() {}
};