#include "Mesh.h"
#include "OpenGL.h"
#include <iostream>

Mesh::Mesh(const std::vector<Vertex> &vertices, const Texture& texture) :
	_vertices(vertices),
	_texture(texture),
	_vao(0),
	_vbo(0),
	_ebo(0)
{
}

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices, const Texture& texture) :
	_vertices(vertices),
	_indices(indices),
	_texture(texture),
	_vao(0),
	_vbo(0),
	_ebo(0)
{
	setupMesh();
}

Mesh::Mesh(float vertices[], int n, const Texture& texture) :
	_texture(texture),
	_vao(0),
	_vbo(0),
	_ebo(0)
{
	for (int i = 0; i < n; i+=8)
	{
		_vertices.push_back({ glm::vec3(vertices[i], vertices[i + 1], vertices[i + 2]),
			glm::vec2(vertices[i + 3], vertices[i + 4]),
			glm::vec3(vertices[i + 5], vertices[i + 6], vertices[i + 7]) });
	}
	setupMesh();
}

void Mesh::draw() const
{
	if(!_texture.Blank())
		_texture.use();

	glBindVertexArray(_vao);
	//glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	if (!_indices.empty())
	{
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
		glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, nullptr);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, _vertices.size());
	}
	glBindVertexArray(0);
}

void Mesh::setTexture(Texture texture)
{
	_texture = texture;
}

bool Mesh::isTextured() const
{
	return !_texture.Blank();
}

void Mesh::displayVertsData()
{
	static int num = 0;
	std::cout << "mesh " << num++ << std::endl;
	for (unsigned int i = 0; i < _vertices.size(); i+=100)
	{
		std::cout << "pos: " << _vertices[i].Position.x << " ," 
			<< _vertices[i].Position.y << " ," 
			<< _vertices[i].Position.z << std::endl;
		std::cout << "tex: " << _vertices[i].TexCoords.x << " ," << _vertices[i].TexCoords.y << std::endl;
		std::cout << "nor: " << _vertices[i].Normal.x << " ," 
			<< _vertices[i].Normal.y << " ,"
			<< _vertices[i].Normal.z << std::endl;
	}
	std::cin.get();
}

void Mesh::setupMesh()
{
	//displayVertsData();
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glGenBuffers(1, &_ebo);
	
	glBindVertexArray(_vao);
	
	// setup mesh data
	// ---------------
	// vertices
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices[0], GL_STATIC_DRAW);
	// indices
	if (!_indices.empty())
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &_indices[0], GL_STATIC_DRAW);
	}

	// setup layout
	// -------------
	// positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
	// texture coordinates
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	// normals
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(5 * sizeof(float)));

	glBindVertexArray(0);
}