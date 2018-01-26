#pragma once

#include "ModelInstance.h"
#include "Camera.h"

#include <vector>
namespace gle
{

class Scene
{
public:
	std::vector<ModelInstance> objects;
	Camera camera;
	Scene(int width, int height) : camera(width, height)
	{}
	void addObject(ModelInstance &model)
	{
		objects.push_back(model);
	}
	void addObject(Model &model)
	{
		objects.push_back(ModelInstance(model));
	}
	void addObject(Model &model, glm::vec3 position)
	{
		objects.push_back(ModelInstance(model, position));
	}
	void addObject(Model &model, glm::vec3 position, glm::vec3 rotation)
	{
		objects.push_back(ModelInstance(model, position, rotation));
	}
	void addObject(Model &model, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
	{
		objects.push_back(ModelInstance(model, position, rotation, scale));
	}
	void addObject(Model &model, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 color)
	{
		objects.push_back(ModelInstance(model, position, rotation, scale, color));
	}
	void Draw(Shader shader)
	{
		glm::mat4 view = camera.getViewMatrix(),
			projection = camera.getProjectionMatrix();

		shader.use();
		shader.setVec3("viewPos", camera.Position);
		shader.setMat4("view", view);
		shader.setMat4("projection", projection);
		//shader.setFloat("time", deltaTime);

		for (int i = 0; i < objects.size(); i++)
			objects[i].Draw(shader);
	}
	void ProcessKeyboard(Camera_Movement direction, bool shift, bool space, float deltaTime)
	{
		camera.ProcessKeyboard(direction, shift, space, deltaTime);
	}
	void ProcessMouseMovement(float xoffset, float yoffset)
	{
		camera.ProcessMouseMovement(xoffset, yoffset);
	}
	void ProcessMouseScroll(float offset)
	{
		camera.ProcessMouseScroll(offset);
	}
};

}