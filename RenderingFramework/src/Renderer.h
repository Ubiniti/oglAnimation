#pragma once

#include "Camera.h"
#include "Scene.h"
#include "Texture2D.h"


#include "Clock.h"
#include "Keyboard.h"
#include "Mouse.h"

std::ostream& operator<<(std::ostream& stream, glm::vec3 v);

std::ostream& operator<<(std::ostream& stream, DirectLight dl);

std::ostream& operator<<(std::ostream& stream, PointLight pl);

/*	Renderer is responsble for drawing 2d and 3d objects on screen
*/
class Renderer
{
	static glm::mat4 model;
	static glm::mat4 view;
	static glm::mat4 projection;
public:
	static void Draw(const Camera & camera, const Shader & shader3d, const Scene & scene);

	static void Draw(const Camera & camera, const Shader & shader3d, Model & model3d);

	static void Draw(const Camera & camera, const Shader & shader3d, Mesh & mesh);

	static void Draw(GLFWwindow* window, const Shader & shader2d, Texture2D & texture);
};