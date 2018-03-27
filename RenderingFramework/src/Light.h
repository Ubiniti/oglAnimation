#pragma once

#include <glm/glm.hpp>

struct DirectLight
{
	glm::vec3 Direction;
	glm::vec3 Ambient;
	glm::vec3 Diffuse;
	glm::vec3 Specular;
	float Strength;
};

struct PointLight
{
	glm::vec3 Position;
	glm::vec3 Ambient;
	glm::vec3 Diffuse;
	glm::vec3 Specular;

	float Constant;
	float Liniear;
	float Quadratic;
	float Strength;
};