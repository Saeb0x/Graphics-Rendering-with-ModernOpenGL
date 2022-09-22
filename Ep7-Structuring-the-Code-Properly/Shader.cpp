#include "Shader.h"

Shader::Shader()
{
	shaderID = 0;
}

void Shader::createShaderFromString(const GLchar* vertexCode, const GLchar* fragmentCode)
{
	compileShader(vertexCode, fragmentCode);
}

void Shader::compileShader(const GLchar* vertexCode, const GLchar* fragmentCode)
{
	shaderID = glCreateProgram();

	addShader(shaderID, vertexCode, GL_VERTEX_SHADER);
	addShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	glLinkProgram(shaderID);

	GLint result = 0;
	GLchar infoLog[1024] = { 0 };

	// Error handling
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(infoLog), NULL, infoLog);
		printf("Error while linking the Shader Program: %s", infoLog);
		return;
	}

	glValidateProgram(shaderID);

	// Error handling
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(infoLog), NULL, infoLog);
		printf("Error while Validating the Shader Program: %s", infoLog);
		return;
	}
}

void Shader::addShader(GLuint shaderProgramHandle, const GLchar* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint theCodeLength[1];
	theCodeLength[0] = strlen(theCode[0]);

	glShaderSource(theShader, 1, theCode, theCodeLength);

	GLint result = 0 ;
	GLchar infoLog[1024] = {0};

	glCompileShader(theShader);
	
	// Error handling
	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, sizeof(infoLog), NULL, infoLog);
		printf("Error while compiling the %s shader: %s", shaderCode, infoLog);
		return;
	}

	glAttachShader(shaderProgramHandle, theShader);
}

void Shader::createShaderFromFiles(const GLchar* vertexLocation, const GLchar* fragmentLocation)
{
	std::string vertexShader = readShaderFile(vertexLocation);
	std::string fragmentShader = readShaderFile(fragmentLocation);

	compileShader(vertexShader.c_str(), fragmentShader.c_str());
}

std::string Shader::readShaderFile(const GLchar* shaderLocation)
{
	std::string fileContent;
	std::ifstream iFileStream(shaderLocation, std::ios::in);

	if (!iFileStream.is_open())
	{
		printf("Error while opening the %s shader file!", shaderLocation);
		return "";
	}

	std::string line = "";
	while (!iFileStream.eof())
	{
		std::getline(iFileStream, line);
		fileContent.append(line + "\n");
	}

	iFileStream.close();
	return fileContent;
}

void Shader::useShader()
{
	glUseProgram(shaderID);
}

void Shader::clearShader()
{
	if (shaderID != 0)
	{
		glDeleteProgram(shaderID);
		shaderID = 0;
	}
}

Shader::~Shader()
{
	clearShader();
}