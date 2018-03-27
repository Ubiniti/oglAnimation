#pragma once

/*	File contains header files needed for using OpenGL
	and error checking functions.
*/

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>

#define ASSERT(x) if(!x) __debugbreak()
#define GlCall(x) GlCleanErrors(); \
	x; \
	ASSERT(!GlLogCall(#x, __FILE__, __LINE__));

static void GlCleanErrors()
{
	while (glGetError() != GL_NO_ERROR);
}

static std::string GlErrToString(GLenum err)
{
	std::string errstr;
	switch (err)
	{
	case GL_INVALID_ENUM:
		errstr = "GL_INVALID_ENUM";
		break;
	case GL_INVALID_VALUE:
		errstr = "GL_INVALID_VALUE";
		break;
	case GL_INVALID_OPERATION:
		errstr = "GL_INVALID_OPERATION";
		break;
	case GL_STACK_OVERFLOW:
		errstr = "GL_STACK_OVERFLOW";
		break;
	case GL_STACK_UNDERFLOW:
		errstr = "GL_STACK_UNDERFLOW";
		break;
	case GL_OUT_OF_MEMORY:
		errstr = "GL_OUT_OF_MEMORY";
		break;
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		errstr = "GL_INVALID_FRAMEBUFFER_OPERATION";
		break;
	default:
		errstr = "Undefined error";
		break;
	}
	return errstr;
}

// check for errors and print info if found any
static bool GlLogCall(const char* function, const char* file, int line)
{
	bool found_err = false;
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		found_err = true;
		std::cout << "[OpenGl] error: "
			<< file << " (" << line << ") | "
			<< function << " : "
			<< GlErrToString(err) << std::endl;
	}
	return found_err;
}

static bool GlLogCall()
{
	return GlLogCall("undef", "undef", -1);
}