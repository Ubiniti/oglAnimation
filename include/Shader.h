#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

namespace gle {

class Shader
{
public:
	//the program ID
	unsigned int ID;

	// constructor generates a shader on the fly
	Shader(const GLchar * vertexPath, const GLchar * fragmentPath, const GLchar * geometryPath = nullptr);
	// use/activate shader
	void use();
	// utility uniform functions
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setMat4(const std::string &name, glm::mat4 matrix4) const;
	void setVec3(const std::string &name, glm::vec3 vec) const;
	void setVec3(const std::string &name, float x, float y, float z) const;

private:
	// allows to load source code file form specified path
	std::string loadSourceFromFile(const GLchar * path);
	// creates and compiles shader of given type
	void compile(unsigned int & shader, std::string sourceCode, GLuint type);
	// creates shader program and links all given shaders
	void createProgram(unsigned int vertexShader, unsigned int fragmentShader);
	void createProgram(unsigned int vertexShader, unsigned int fragmentShader, unsigned int geometryShader);
	// chekcs for shader compilation errors and outputs result in console
	void checkCompileErrors(unsigned int shader, const std::string type);
};

}