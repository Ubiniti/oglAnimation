#include "Shader.h"

#include <sstream>
#include <string>
#include <iostream>
#include <fstream>

unsigned int Shader::activeShader = 0;

Shader::~Shader()
{
	glDeleteProgram(ID);
}

void Shader::use() const
{
	if (activeShader != ID)
	{
		glUseProgram(ID);
		activeShader = ID;
	}
}

void Shader::setBool(const char * paramName, bool value) const
{
	use();
	glUniform1ui(glGetUniformLocation(ID, paramName), value);
}

void Shader::setUInt(const char * paramName, unsigned int value) const
{
	use();
	glUniform1ui(glGetUniformLocation(ID, paramName), value);
}

void Shader::setFloat(const char * paramName, float value) const
{
	use();
	glUniform1f(glGetUniformLocation(ID, paramName), value);
}

void Shader::setVec2(const char * paramName, glm::vec2 value) const
{
	use();
	glUniform2f(glGetUniformLocation(ID, paramName), value.x, value.y);
}

void Shader::setVec3(const char * paramName, glm::vec3 value) const
{
	use();
	glUniform3f(glGetUniformLocation(ID, paramName), value.x, value.y, value.z);
}

void Shader::setVec4(const char* paramName, glm::vec4 value) const
{
	use();
	glUniform4f(glGetUniformLocation(ID, paramName), value.x, value.y, value.z, value.w);
}

void Shader::setMat4(const char * paramName, glm::mat4 value) const
{
	use();
	GlCall(glUniformMatrix4fv(glGetUniformLocation(ID, paramName), 1, GL_FALSE, glm::value_ptr(value)));
}

void Shader::setDirLight(const char * paramName, DirectLight value) const
{
	setVec3(std::string(paramName).append(".ambient").c_str(), value.Ambient);
	setVec3(std::string(paramName).append(".diffuse").c_str(), value.Diffuse);
	setVec3(std::string(paramName).append(".specular").c_str(), value.Specular);
	setVec3(std::string(paramName).append(".direction").c_str(), value.Direction);
	setFloat(std::string(paramName).append(".strength").c_str(), value.Strength);
}

void Shader::setPointLight(const char * paramName, unsigned int index, PointLight value) const
{
	std::stringstream ss;

	ss << paramName << "[" << index << "]" << ".ambient";
	setVec3(ss.str().c_str(), value.Ambient);
	ss.str(std::string());
	ss << paramName << "[" << index << "]" << ".diffuse";
	setVec3(ss.str().c_str(), value.Diffuse);
	ss.str(std::string());
	ss << paramName << "[" << index << "]" << ".specular";
	setVec3(ss.str().c_str(), value.Specular);
	ss.str(std::string());
	ss << paramName << "[" << index << "]" << ".position";
	setVec3(ss.str().c_str(), value.Position);
	ss.str(std::string());
	ss << paramName << "[" << index << "]" << ".constant";
	setFloat(ss.str().c_str(), value.Constant);
	ss.str(std::string());
	ss << paramName << "[" << index << "]" << ".liniear";
	setFloat(ss.str().c_str(), value.Liniear);
	ss.str(std::string());
	ss << paramName << "[" << index << "]" << ".quadratic";
	setFloat(ss.str().c_str(), value.Quadratic);
	ss.str(std::string());
	ss << paramName << "[" << index << "]" << ".strength";
	setFloat(ss.str().c_str(), value.Strength);
	ss.str(std::string());
}

void Shader::setTextureLayout(unsigned int diffuseTextureSlot) const
{
	use();
	setUInt("material.textureDiffuse", diffuseTextureSlot);
}

unsigned int Shader::CreateShaderProgram(const std::string &vertexSource, const std::string &fragmentSource) const
{
	const unsigned int logBufSize = 1024;
	char infoLog[logBufSize];
	int success;
	unsigned int program = glCreateProgram(),
		vs = CompileShader(vertexSource.c_str(), GL_VERTEX_SHADER),
		fs = CompileShader(fragmentSource.c_str(), GL_FRAGMENT_SHADER);
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (success != GL_TRUE)
	{
		glGetProgramInfoLog(program, logBufSize, NULL, infoLog);
		std::cout << infoLog << std::endl;
	}
	glDeleteShader(vs);
	glDeleteShader(fs);
	return program;
}

unsigned int Shader::CompileShader(const char* source, unsigned int shaderType) const
{
	const unsigned int logBufSize = 1024;
	unsigned int shader = glCreateShader(shaderType);
	int success;
	char infoLog[logBufSize];
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (success != GL_TRUE)
	{
		glGetShaderInfoLog(shader, logBufSize, NULL, infoLog);
		std::cout << infoLog << std::endl;
	}
	return shader;
}

std::string Shader::LoadFromFile(const char* path) const
{
	std::string output;
	std::ifstream filestream;
	filestream.open(path);
	if (filestream.is_open())
	{
		std::string line;
		while (std::getline(filestream, line))
		{
			output += line + '\n';
		}
	}
	else
	{
		std::cout << "Error while loading file from: " << path << std::endl;
	}
	return output;
}