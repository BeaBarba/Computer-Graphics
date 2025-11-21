#pragma once

#include "lib.h"
#include "StbImage.h"
#include <time.h>

class ShaderMaker
{
public:
	static char* readShaderSource(const char* shaderFile);
	static GLuint createProgram(char* vertexfilename, char* fragmentfilename);
	static GLuint initShader(char* vertexShader, char* fragmentShader);
	static GLuint setupTexture(const char* image_name);
	static void useShaderWithUniform(unsigned int shader_program_id, mat4& projection, mat4& model, float currentTime, vec2 resolution, bool texture, bool date);

private:
	ShaderMaker() {}
};