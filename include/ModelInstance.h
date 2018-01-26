#pragma once

#include "Model.h"

namespace gle
{

class ModelInstance
{
	Model* model;
public:
	glm::vec3 Color;
	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 GlobalRotation;
	glm::vec3 Scale;
	ModelInstance(Model &model,
		glm::vec3 position = glm::vec3(0.0f),
		glm::vec3 rotation = glm::vec3(1.0f),
		glm::vec3 scale = glm::vec3(1.0f),
		glm::vec3 color = glm::vec3(1.0f)) :
			model(&model),
			Position(position),
			GlobalRotation(rotation),
			Rotation(glm::vec3(0.0f)),
			Scale(scale),
			Color(color)
	{}
	void Draw(Shader shader)
	{
		model->Draw(shader, Position, Rotation + GlobalRotation, Scale, Color);
	}
	void Rotate(glm::vec3 rotation)
	{
		Rotation += rotation;
	}
};

}