#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace gle {

class Keyboard
{
public:
	enum Key {
		A = GLFW_KEY_A,
		B = GLFW_KEY_B,
		C = GLFW_KEY_C,
		D = GLFW_KEY_D,
		E = GLFW_KEY_E,
		F = GLFW_KEY_F,
		G = GLFW_KEY_G,
		H = GLFW_KEY_H,
		I = GLFW_KEY_I,
		J = GLFW_KEY_J,
		K = GLFW_KEY_A,
		L = GLFW_KEY_A,
		M = GLFW_KEY_A,
		N = GLFW_KEY_A,
		O = GLFW_KEY_A,
		P = GLFW_KEY_A,
		Q = GLFW_KEY_A,
		R = GLFW_KEY_A,
		S = GLFW_KEY_S,
		T = GLFW_KEY_A,
		U = GLFW_KEY_A,
		V = GLFW_KEY_A,
		W = GLFW_KEY_A,
		X = GLFW_KEY_A,
		Y = GLFW_KEY_A,
		Z = GLFW_KEY_A,
		LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT,
		RIGHT_SHIFT = GLFW_KEY_RIGHT_SHIFT,
		SPACE = GLFW_KEY_SPACE,
		DOWN = GLFW_KEY_DOWN,
		LEFT = GLFW_KEY_LEFT,
		RIGHT = GLFW_KEY_RIGHT,
		UP = GLFW_KEY_UP,
		ESCAPE = GLFW_KEY_ESCAPE
	};
	static bool isKeyPreesed(Key key);
};

}