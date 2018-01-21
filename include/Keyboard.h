#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace gle {

class Keyboard
{
public:
	enum Key {
		A = GLFW_KEY_A,
		D = GLFW_KEY_D,
		F = GLFW_KEY_F,
		H = GLFW_KEY_H,
		S = GLFW_KEY_S,
		LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT,
		RIGHT_SHIFT = GLFW_KEY_RIGHT_SHIFT,
		SPACE = GLFW_KEY_SPACE,
		W = GLFW_KEY_W,
		DOWN = GLFW_KEY_DOWN,
		LEFT = GLFW_KEY_LEFT,
		RIGHT = GLFW_KEY_RIGHT,
		UP = GLFW_KEY_UP,
		ESCAPE = GLFW_KEY_ESCAPE
	};
	static bool isKeyPreesed(Key key);
};

}