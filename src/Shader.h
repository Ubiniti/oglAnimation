#pragma once

#include "OpenGL.h"
#include "Light.h"

#include <string>

/*	Controlls shader porgram on GPU.
*/
class Shader
{
	static unsigned int activeShader; // id of currently bound program
public:
	unsigned int ID;
	Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
	{
		ID = CreateShaderProgram(LoadFromFile(vertexShaderPath), LoadFromFile(fragmentShaderPath));
	}
	~Shader();
	void use() const;
	void setBool(const char * paramName, bool value) const;
	void setUInt(const char * paramName, unsigned int value) const;
	void setFloat(const char * paramName, float value) const;
	void setVec2(const char* paramName, glm::vec2 value) const;
	void setVec3(const char* paramName, glm::vec3 value) const;
	void setVec4(const char* paramName, glm::vec4 value) const;
	void setMat4(const char* paramName, glm::mat4 value) const;
	void setDirLight(const char* paramName, DirectLight value) const;
	void setPointLight(const char* paramName, unsigned int index, PointLight value) const;
	void setTextureLayout(unsigned int diffuseTextureSlot = 0) const;
private:
	unsigned int CreateShaderProgram(const std::string &vertexSource, const std::string &fragmentSource) const;
	unsigned int CompileShader(const char* source, unsigned int shaderType) const;
	std::string LoadFromFile(const char* path) const;
};