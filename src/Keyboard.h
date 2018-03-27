#pragma once

#include "OpenGL.h"
/* Simplifies GLFW keyboard input checking
*/
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
		K = GLFW_KEY_K,
		L = GLFW_KEY_L,
		M = GLFW_KEY_M,
		N = GLFW_KEY_N,
		O = GLFW_KEY_O,
		P = GLFW_KEY_P,
		Q = GLFW_KEY_Q,
		R = GLFW_KEY_R,
		S = GLFW_KEY_S,
		T = GLFW_KEY_T,
		U = GLFW_KEY_U,
		V = GLFW_KEY_V,
		W = GLFW_KEY_W,
		X = GLFW_KEY_X,
		Y = GLFW_KEY_Y,
		Z = GLFW_KEY_Z,
		N0 = GLFW_KEY_0,
		N1 = GLFW_KEY_1,
		N2 = GLFW_KEY_2,
		N3 = GLFW_KEY_3,
		N4 = GLFW_KEY_4,
		N5 = GLFW_KEY_5,
		N6 = GLFW_KEY_6,
		N7 = GLFW_KEY_7,
		N8 = GLFW_KEY_8,
		N9 = GLFW_KEY_9,
		NUM_0 = GLFW_KEY_KP_0,
		NUM_1 = GLFW_KEY_KP_1,
		NUM_2 = GLFW_KEY_KP_2,
		NUM_3 = GLFW_KEY_KP_3,
		NUM_4 = GLFW_KEY_KP_4,
		NUM_5 = GLFW_KEY_KP_5,
		NUM_6 = GLFW_KEY_KP_6,
		NUM_7 = GLFW_KEY_KP_7,
		NUM_8 = GLFW_KEY_KP_8,
		NUM_9 = GLFW_KEY_KP_9,
		LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT,
		RIGHT_SHIFT = GLFW_KEY_RIGHT_SHIFT,
		SPACE = GLFW_KEY_SPACE,
		DOWN = GLFW_KEY_DOWN,
		LEFT = GLFW_KEY_LEFT,
		RIGHT = GLFW_KEY_RIGHT,
		UP = GLFW_KEY_UP,
		ESCAPE = GLFW_KEY_ESCAPE
	};
	static bool isKeyPreesed(GLFWwindow* window, Key key)
	{
		return glfwGetKey(window, key) == GLFW_PRESS;
	}
};