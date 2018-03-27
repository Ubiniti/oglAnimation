#pragma once

#include "Time.h"

/*	Helps with measuring time.
*/
class Clock
{
	Time lastTime; // time on last reset
public:
	Clock()
	{
		reset();
	}
	Time reset()
	{
		Time dtime = glfwGetTime() - lastTime.asSeconds();
		lastTime = glfwGetTime();
		return dtime;
	}
};