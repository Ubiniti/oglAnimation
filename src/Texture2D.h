#pragma once

#include "Texture.h"
#include "Shader.h"

#include "OpenGL.h"

#include <string>
#include <iostream>

/* Allows for simple 2D texture renderig.
*/
class Texture2D : public Texture
{
	unsigned int _vao; // vertex array object
	unsigned int _vbo; // vertex buffer object
public:
	glm::vec2 Position;
	glm::vec2 Size;
	glm::vec2 Scale;
	Texture2D(std::string path, glm::vec2 position) :
		Texture2D(path)
	{}
	Texture2D(std::string path) :
		Texture(path, false, true),
		Position(0.0f),
		Size(0.0f, 0.0f),
		Scale(1.0f)
	{
		Size = glm::vec2(getWidth(), getHeight());
		// rectangle vertices
		float rect[] = {
			// positions	tex-coords
			-1.0f,  1.0f,   0.0f, 1.0f, // TL
			 1.0f,  1.0f,   1.0f, 1.0f, // TR
			 1.0f, -1.0f,   1.0f, 0.0f, // BR

			-1.0f,  1.0f,   0.0f, 1.0f, // TL
			-1.0f, -1.0f,   0.0f, 0.0f, // BL
			 1.0f, -1.0f,   1.0f, 0.0f  // BR
		};
		// setup buffers
		// -------------
		GlCall(glGenVertexArrays(1, &_vao));
		GlCall(glGenBuffers(1, &_vbo));
		GlCall(glBindVertexArray(_vao));
		// set vertices data
		GlCall(glBindBuffer(GL_ARRAY_BUFFER, _vbo));
		GlCall(glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STATIC_DRAW));
		// layout
		// positions
		GlCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)0));
		GlCall(glEnableVertexAttribArray(0));
		// texture coordinates
		GlCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(sizeof(float) * 2)));
		GlCall(glEnableVertexAttribArray(1));

		GlCall(glBindVertexArray(0));
	}
	void draw(GLFWwindow* window, const Shader &shader2d)
	{
		int width, height;
		glfwGetWindowSize(window, &width, &height);
		// calculate scaling value to make texture original size
		glm::vec2 outscale(Size.x / width, Size.y / height);
		// scaling calculated value with Scale property
		outscale *= Scale;
		// bind texture before drawing
		use();
		// upload properties to shader
		shader2d.use();
		shader2d.setVec2("pos2d", Position);
		shader2d.setVec2("scale2d", outscale);
		// draw on screen
		GlCall(glBindVertexArray(_vao));
		GlCall(glBindBuffer(GL_ARRAY_BUFFER, _vbo));
		GlCall(glDrawArrays(GL_TRIANGLES, 0, 6));
	}
};