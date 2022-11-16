#pragma once

#include <string>
#include <stdio.h>
#include <fstream>

#include "GL/glew.h"

class Shader
{
public:
	GLuint uniformModel;
	Shader();
	void createShaderFromString(const GLchar* vertexCode, const GLchar* fragmentCode);
	void createShaderFromFiles(const GLchar* vertexLocation, const GLchar* fragmentLocation);
	void useShader();
	void clearShader();
	~Shader();
private:
	GLuint shaderID; // Shader Program handle
	void addShader(GLuint shaderProgramHandle, const GLchar* shaderCode, GLenum shaderType);
	void compileShader(const GLchar* vertexCode, const GLchar* fragmentCode);
	std::string readShaderFile(const GLchar* shaderLocation);
};

