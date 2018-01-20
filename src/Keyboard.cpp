#include "Keyboard.h"
#include "Window.h"

namespace gle {
// ------------------------------------------------------------------------------------------
bool Keyboard::isKeyPreesed(Key key)
{
	return glfwGetKey(Window::activeGlfwWindow, key) == GLFW_PRESS;
}
// ------------------------------------------------------------------------------------------
}