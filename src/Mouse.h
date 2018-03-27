#pragma once

#include "OpenGL.h"

/*	Allows for mouse input check.
*/
class Mouse
{
public:
	static glm::vec2 getMousePosition(GLFWwindow* window)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return glm::vec2(xpos, ypos);
	}
	static glm::vec2 getMouseMove(GLFWwindow* window)
	{
		static glm::vec2 lastPos = getMousePosition(window);
		glm::vec2 newPos = getMousePosition(window);
		glm::vec2 output = newPos - lastPos;
		lastPos = newPos;
		return output;
	}
};