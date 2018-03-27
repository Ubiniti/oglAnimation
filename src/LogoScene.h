#pragma once

#include "Scene.h"

struct Digit
{
	bool Number;
	glm::vec3 Position;
	float zRotation;
};

class LogoScene : public Scene
{
	Model* _digit0;
	Model* _digit1;
	glm::vec3 _animLightPos;
	std::vector<Digit> _digits;
	glm::vec3 _digitsRotation;
	float _digitsRotationSpeed;
public:
	LogoScene(std::string path) :
		Scene(path),
		_animLightPos(glm::vec3(1.5f, 0.8f, 0.8f)),
		_digitsRotationSpeed(90.0f)
	{
		loadDigitsModels();
		initDigitsPositions();
	}

	void drawDigitsCircle(Shader & shader3d) const;

	void initDigitsPositions(glm::vec3 circlePos = glm::vec3(0.2, 0.2, 0.0),
		unsigned int count = 37,
		float beta = glm::radians(20.0f),
		float gamma = glm::radians(45.0f));

	void loadDigitsModels();

	void update(float deltaTime);

	void updateLightAnimation(float deltaTime);
};