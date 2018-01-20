#include "Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

namespace gle {

// ------------------------------------------------------------------------------------------
Shader::Shader(const GLchar * vertexPath, const GLchar * fragmentPath,
	const GLchar * geometryPath)
{
	unsigned int vertex, fragment, geometry;
	std::string vertexCode, fragmentCode, geometryCode;

	// load vertex and fragment shader source code from files
	vertexCode = loadSourceFromFile(vertexPath);
	fragmentCode = loadSourceFromFile(fragmentPath);
	if (geometryPath != nullptr)
		geometryCode = loadSourceFromFile(geometryPath);

	// vertex shader
	compile(vertex, vertexCode, GL_VERTEX_SHADER);
	checkCompileErrors(vertex, "VERTEX");
	// fragment shader
	compile(fragment, fragmentCode, GL_FRAGMENT_SHADER);
	checkCompileErrors(fragment, "FRAGMENT");
	// geometry shader
	if (geometryPath != nullptr)
	{
		compile(geometry, geometryCode, GL_GEOMETRY_SHADER);
		checkCompileErrors(geometry, "GEOMETRY");
		createProgram(vertex, fragment, geometry);
	}
	else
		createProgram(vertex, fragment);
}
// ------------------------------------------------------------------------------------------
void Shader::use()
{
	glUseProgram(ID);
}
// ------------------------------------------------------------------------------------------
void Shader::setBool(const std::string & name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
// ------------------------------------------------------------------------------------------
void Shader::setInt(const std::string & name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
// ------------------------------------------------------------------------------------------
void Shader::setFloat(const std::string & name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
// ------------------------------------------------------------------------------------------
void Shader::setMat4(const std::string & name, glm::mat4 matrix4) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix4));
}
// ------------------------------------------------------------------------------------------
void Shader::setVec3(const std::string &name, glm::vec3 vec) const
{
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &vec[0]);
}
// ------------------------------------------------------------------------------------------
void Shader::setVec3(const std::string &name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}
// ------------------------------------------------------------------------------------------
std::string Shader::loadSourceFromFile(const GLchar * path)
{
	std::string sourceCode;
	std::ifstream sFile;

	// ensure ifstream object can throw exceptions
	sFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		sFile.open(path);
		// read file buffer content into stream
		std::stringstream sourceStream;
		sourceStream << sFile.rdbuf();
		// close file handler
		sFile.close();
		// convert stream to string
		sourceCode = sourceStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER:FILE_NOT_SUCCESLULLY_READ" << std::endl;
	}

	return sourceCode;
}
// ------------------------------------------------------------------------------------------
void Shader::compile(unsigned int & shader, std::string sourceCode, GLuint type)
{
	const char* code = sourceCode.c_str();

	shader = glCreateShader(type);
	glShaderSource(shader, 1, &code, NULL);
	glCompileShader(shader);
}
// ------------------------------------------------------------------------------------------
void Shader::createProgram(unsigned int vertexShader, unsigned int fragmentShader)
{
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	checkCompileErrors(ID, "PROGRAM");
	// delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
// ------------------------------------------------------------------------------------------
void Shader::createProgram(unsigned int vertexShader, unsigned int fragmentShader,
	unsigned int geometryShader)
{
	// shader program
	ID = glCreateProgram();
	// link shaders
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glAttachShader(ID, geometryShader);
	glLinkProgram(ID);
	checkCompileErrors(ID, "PROGRAM");
	// delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(geometryShader);
}
// ------------------------------------------------------------------------------------------
void Shader::checkCompileErrors(unsigned int shader, const std::string type)
{
	int succes;
	char infoLog[1024];

	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &succes);
		if (!succes)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << std::endl
				<< infoLog << std::endl << "-- ------------------------------- --"
				<< std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &succes);
		if (!succes)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << std::endl
				<< infoLog << std::endl << "-- ------------------------------- --"
				<< std::endl;
		}
	}
}
// ------------------------------------------------------------------------------------------

}