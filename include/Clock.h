#pragma once

#include "Time.h"

#include <GLFW/glfw3.h>

namespace gle
{

	class Clock
	{
		Time time;
		Time lastTime;
	public:
		Clock() : time(glfwGetTime())
		{}

		Time reset()
		{
			Time dtime = glfwGetTime() - lastTime.asSeconds();
			lastTime = glfwGetTime();
			return dtime;
		}
	};

}