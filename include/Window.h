#pragma once
#include "Color.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Event.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <queue>

namespace gle {

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void mousemove_callback(GLFWwindow * window, double xpos, double ypos);

void mousebtn_callback(GLFWwindow * window, int button, int action, int mods);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

class Window
{
	GLFWwindow* glfwWindow;
	static GLFWwindow* activeGlfwWindow;
	static Window* activeWindow;
	std::queue<Event> _events;
public:
	friend Keyboard;
	friend Mouse;
	friend void framebuffer_size_callback(GLFWwindow*, int, int);
	friend void scroll_callback(GLFWwindow*, double, double);
	friend void mousemove_callback(GLFWwindow*, double, double);
	friend void mousebtn_callback(GLFWwindow*, int, int, int);
	friend void key_callback(GLFWwindow*, int, int, int, int);

	Window(int width, int height, const char* title);
	~Window();

	void clear();

	void clear(Color color);

	void close();

	void display();

	bool isOpen();

	bool pollEvents(Event &ev);

	void setVerticalSyncEnabled(bool enable);
private:
};

}