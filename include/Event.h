#pragma once
#include "Keyboard.h"
#include "Mouse.h"
#include <glm/glm.hpp>

namespace gle {

class Event
{
public:
	enum EventType {
		Closed,
		Resized,
		KeyPressed,
		KeyReleased,
		MouseWheelScrolled,
		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved
	};
	EventType type;

	struct SizeEvent
	{
		unsigned int width, height;
	};

	struct KeyEvent
	{
		Keyboard::Key code;
		bool alt,
			control,
			shift,
			system;
	};

	struct MouseMoveEvent
	{
		int x, y;
	};

	struct MouseScrollEvent
	{
		int delta;
	};

	struct MouseButtonEvent
	{
		Mouse::Button button;
		int x, y;
	};

	union
	{
		SizeEvent size;
		KeyEvent key;
		MouseMoveEvent mouseMove;
		MouseScrollEvent mouseScroll;
		MouseButtonEvent mouseButton;
	};
};

}