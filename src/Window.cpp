#include "Window.h"

namespace gle {

GLFWwindow* Window::activeGlfwWindow;
Window* Window::activeWindow;
// ------------------------------------------------------------------------------------------
Window::Window(int width, int height, const char* title)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
	#endif

	// glfw window creation
	// --------------------
	glfwWindow = glfwCreateWindow(width, height, title, NULL, NULL);
	if (glfwWindow == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		close();
	}
	glfwMakeContextCurrent(glfwWindow);

	glfwSwapInterval(0);

	glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetFramebufferSizeCallback(glfwWindow, framebuffer_size_callback);
	glfwSetCursorPosCallback(glfwWindow, mousemove_callback);
	glfwSetMouseButtonCallback(glfwWindow, mousebtn_callback);
	glfwSetScrollCallback(glfwWindow, scroll_callback);
	glfwSetKeyCallback(glfwWindow, key_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		close();
	}

	activeGlfwWindow = glfwWindow;
	activeWindow = this;
}
// ------------------------------------------------------------------------------------------
Window::~Window()
{
	glfwTerminate();
}
// ------------------------------------------------------------------------------------------
void Window::clear()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
// ------------------------------------------------------------------------------------------
void Window::clear(Color color)
{
	glClearColor(color.r, color.g, color.b, color.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
// ------------------------------------------------------------------------------------------
void Window::close()
{
	glfwSetWindowShouldClose(glfwWindow, true);
}
// ------------------------------------------------------------------------------------------
void Window::display()
{
	glfwSwapBuffers(glfwWindow);
}
// ------------------------------------------------------------------------------------------
bool Window::isOpen()
{
	return !glfwWindowShouldClose(glfwWindow);
}
// ------------------------------------------------------------------------------------------
bool Window::pollEvents(Event &ev)
{
	if (_events.size() > 0)
	{
		ev = Event(_events.front());
		_events.pop();
		return true;
	}
	return false;
}
// ------------------------------------------------------------------------------------------
void Window::setVerticalSyncEnabled(bool enable)
{
	glfwSwapInterval((int)enable);
}
// ------------------------------------------------------------------------------------------
static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
// ------------------------------------------------------------------------------------------
static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Event ev;
	ev.type = Event::MouseWheelScrolled;
	ev.mouseScroll.delta = yoffset;
	Window::activeWindow->_events.push(ev);
	//mainCamera.ProccesMouseScroll((float)yoffset);
}
// ------------------------------------------------------------------------------------------
static void mousemove_callback(GLFWwindow * window, double xpos, double ypos)
{
	static float lastX = (float)xpos;
	static float lastY = (float)ypos;
	float xoffset = (float)xpos - lastX,
		yoffset = (float)ypos - lastY;
	lastX = (float)xpos;
	lastY = (float)ypos;

	Event ev;
	ev.type = Event::MouseMoved;
	ev.mouseMove.x = xoffset;
	ev.mouseMove.y = yoffset;
	Window::activeWindow->_events.push(ev);
}
// ------------------------------------------------------------------------------------------
static void mousebtn_callback(GLFWwindow * window, int button, int action, int mods)
{
	Event ev;
	ev.type = Event::MouseButtonPressed;
	ev.mouseButton.button = (Mouse::Button)button;
	Window::activeWindow->_events.push(ev);
}
// ------------------------------------------------------------------------------------------
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Event ev;
	ev.type = action == GLFW_PRESS ? Event::KeyPressed : Event::KeyReleased;
	ev.key.code = (Keyboard::Key)key;
	ev.key.shift = GLFW_MOD_SHIFT & mods;
	ev.key.control = GLFW_MOD_CONTROL & mods;
	ev.key.alt = GLFW_MOD_ALT & mods;
	ev.key.system = GLFW_MOD_SUPER & mods;
	Window::activeWindow->_events.push(ev);
}
// ------------------------------------------------------------------------------------------
}