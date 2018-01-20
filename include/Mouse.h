#pragma once
#include "Vector2.h"
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace gle {

class Mouse
{
public:
	enum Button {
		Right = GLFW_MOUSE_BUTTON_RIGHT,
		Left = GLFW_MOUSE_BUTTON_LEFT,
		Middle = GLFW_MOUSE_BUTTON_MIDDLE
	};
	static bool isButtonPressed(Button btn);
	static Vector2i getMousePosition();
};

}