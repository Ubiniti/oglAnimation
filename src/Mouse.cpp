#include "Mouse.h"
#include "Window.h"

namespace gle {
// ------------------------------------------------------------------------------------------
bool Mouse::isButtonPressed(Button btn)
{
	return glfwGetMouseButton(Window::activeGlfwWindow, btn) == GLFW_PRESS;
}
// ------------------------------------------------------------------------------------------
Vector2i Mouse::getMousePosition()
{
	double xpos, ypos;
	glfwGetCursorPos(Window::activeGlfwWindow, &xpos, &ypos);
	return Vector2i((int)xpos, (int)ypos);
}
// ------------------------------------------------------------------------------------------
}