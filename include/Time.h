#pragma once

#include <GLFW/glfw3.h>

namespace gle
{

struct Time
{
	double time;
public:
	Time() : time(0.0)
	{}
	Time(double timeSeconds) : time(timeSeconds)
	{}
	double asSeconds()
	{
		return time;
	}
	double asMiliseconds()
	{
		return time * 1000;
	}
};

}