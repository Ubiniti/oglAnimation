#pragma once

#include "Texture.h"

#include <vector>
#include <glm/glm.hpp>

struct Vertex
{
	glm::vec3 Position;
	glm::vec2 TexCoords;
	glm::vec3 Normal;
};

class Mesh
{
	std::vector<Vertex> _vertices;
	std::vector<unsigned int> _indices;
	Texture _texture;
	unsigned int _vao, _vbo, _ebo;
public:
	Mesh(const std::vector<Vertex> &vertices, const Texture& texture);
	Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices, const Texture& texture);
	Mesh(float vertices[], int n, const Texture& texture);
	void draw() const;
	void setTexture(Texture texture);
	bool isTextured() const;
private:
	/*	Loads vertices and indices to GPU memory
		and defines data layout.
	*/
	void displayVertsData();
	void setupMesh();
};