#pragma once

#include "Light.h"

namespace gle
{

class SpotLight : public Light
{
	float constant = 1.0f;
	float linear = 0.09f;
	float quadratic = 0.032f;
public:
	glm::vec3 Position;
	glm::vec3 Direction;
	float radious = 12.5f;
	float outerRadious = 15.0f;
	SpotLight(glm::vec3 position,
		glm::vec3 direction = glm::vec3(0.0),
		glm::vec3 ambient = glm::vec3(0.2),
		glm::vec3 diffuse = glm::vec3(0.1),
		glm::vec3 specular = glm::vec3(1.0))
		: SpotLight(12.5f, 15.0f, position, direction, ambient, diffuse, specular)
	{}
	SpotLight(float radious,
		float outerradious,
		glm::vec3 position,
		glm::vec3 direction = glm::vec3(0.0),
		glm::vec3 ambient = glm::vec3(0.2),
		glm::vec3 diffuse = glm::vec3(0.1),
		glm::vec3 specular = glm::vec3(1.0))
		: Light(Point, ambient, diffuse, specular),
		radious(radious),
		outerRadious(outerradious),
		Position(position),
		Direction(direction)
	{}
	void upload(Shader shader)
	{
		shader.setVec3("spotLight.ambient", ambient);
		shader.setVec3("spotLight.diffuse", diffuse);
		shader.setVec3("spotLight.specular", specular);

		shader.setVec3("spotLight.position", Position);
		shader.setVec3("spotLight.direction", Direction);
		shader.setFloat("spotLight.cutOff", glm::cos(glm::radians(radious)));
		shader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(outerRadious)));

		shader.setFloat("spotLight.constant", constant);
		shader.setFloat("spotLight.linear", linear);
		shader.setFloat("spotLight.quadratic", quadratic);
	}
};

}