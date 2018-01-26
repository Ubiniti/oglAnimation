#pragma once

#include "Light.h"

namespace gle
{

class DirLight : public Light
{
public:
	glm::vec3 Direction;
	DirLight(glm::vec3 direction, glm::vec3 ambient = glm::vec3(0.2),
		glm::vec3 diffuse = glm::vec3(0.1),
		glm::vec3 specular = glm::vec3(1.0)) :
		Light(Point, ambient, diffuse, specular),
		Direction(direction)
	{}
	void upload(Shader shader)
	{
		shader.setVec3("dirLight.direction", Direction);
		shader.setVec3("dirLight.ambient", ambient);
		shader.setVec3("dirLight.diffuse", diffuse);
		shader.setVec3("dirLight.specular", specular);
	}
};

}