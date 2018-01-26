#pragma once

#include "Scene.h"

#include <GLFW/glfw3.h>

namespace gle
{
class LogoScene : public Scene
{
	int digitsStartIndex;
	int digitsLastIndex;
	int lapmId;
	bool firstDrawCall = false;
	glm::vec3 spotLightDir = glm::vec3(0.0);
	glm::vec3 spotLightPos = glm::vec3(0.0);
public:
	LogoScene(int width, int height) :
		Scene(width, height)
	{}
	void load(Shader shader, Model models[], glm::vec3 lightPositions[])
	{
		addObject(models[2], glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.75f, 0.0f, 0.0f), glm::vec3(1.0f),
			glm::vec3(0.2f, 0.3f, 1.0f));
		addObject(models[3], glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.75f, 0.0f, 0.0f));
		loadAnimDigits(models);
	}
	void update(Shader shader, double deltaTime)
	{
		for (int i = digitsStartIndex; i < digitsLastIndex; i++)
			objects[i].Rotate(glm::vec3(0.0, 0.0, 0.15*deltaTime));

		shader.setVec3("spotLight.position", camera.Position);
		shader.setVec3("spotLight.direction", camera.Front);
	}
private:
	void loadAnimDigits(Model models[], int count = 37, float beta = glm::radians(20.0f), float gamma = glm::radians(45.0f))
	{
		// TODO : refactor
		glm::vec3 circlePos(0.2, 0.2, 0.0);
		beta = glm::radians(20.0f);
		gamma = glm::radians(45.0f);
		count = 37;
		digitsStartIndex = objects.size();
		digitsLastIndex = count + 2;
		const float PI = glm::pi<double>();
		float alpha = (2 * PI - beta - gamma) / count;
		float r = 1.5;
		glm::vec3 pos(0.0, 0.0, 0.0);
		float rotation, nAlpha = (alpha / (2 * PI)),
			nBeta = beta / (2 * PI),
			nGamma = gamma / (2 * PI);

		glm::vec3 scale(1.0);
		for (int i = 0; i < count; i++)
		{
			//angle = alpha * i + beta;
			rotation = 0.25 - nAlpha * i - nBeta;
			pos.x = cos(alpha * i + beta)*r + circlePos.x;
			pos.y = sin(alpha * i + beta)*r + circlePos.y;
			addObject(models[i % 2], pos, 
				glm::vec3(0.75f, rotation, 
				((int)(glfwGetTime() * 1000000000) % 1000) / 1000.0f), 
				scale,
				glm::vec3(244 / 255.0f, 226 / 255.0f, 66 / 255.0f));
		}
	}
};
}