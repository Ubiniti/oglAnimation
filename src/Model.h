#pragma once

#include "Texture.h"
#include "Mesh.h"
#include "Shader.h"

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include <string>
#include <iostream>

#define LOAD_TEXTURES true
#define NO_TEXTURES false

/*	Contains 3D model loaded from a file.
*/
class Model
{
	std::vector<Texture> _textures;
	std::vector<Mesh> _meshes;
	std::string _directory;
	const glm::vec3 _initRotation;
public:
	glm::vec3 Position;
	glm::vec3 Scale;
	glm::vec3 Rotation;
	glm::vec3 Color;
	/*	Rotation is baked during loading
	*/
	Model(std::string modelPath, glm::vec3 rotation = glm::vec3(0.0f)) :
		Scale(1.0f),
		Color(1.0f),
		Rotation(0.0f),
		_initRotation(rotation)
	{
		loadFromFile(modelPath);
	}
	/*	Constructior loads model and sets one texture for all meshes.
	*/
	Model(std::string modelPath, std::string texturePath, glm::vec3 rotation = glm::vec3(0.0f)) :
		Scale(1.0f),
		Color(1.0f),
		Rotation(0.0f),
		_initRotation(rotation)
	{
		loadFromFile(modelPath);
		
		if (!texturePath.empty())
		{
			_textures.clear();
			_textures.push_back(Texture(texturePath));
			for (unsigned int i = 0; i < _meshes.size(); i++)
			{
				//std::cout << "isTextureBlank: " << _textures[0].Blank() << std::endl;
				_meshes[i].setTexture(_textures[0]);
			}
		}
	}

	// DEBUGING : logs textures contained in specified scene
	void printLinkedTextures(const aiScene* scene) const;

	void draw(const Shader & shader) const;

	/*	Return true if model has any textures
	*/
	bool isTextured();
private:
	/*	Return true if any meshes loaded
	*/
	bool empty();

	/*	Get first texture path of a given type found in a model file
	*/
	std::string getTexturePath(const aiMaterial* material, aiTextureType type);

	/*	Load material texture
		if was not loaded before
	*/
	Texture loadTexture(const aiScene* scene, const aiMaterial* material);

	/*	Load mesh with specified rotation in degrees
	*/
	Mesh loadMesh(const aiScene* scene, const aiMesh *mesh);

	void loadFromFile(std::string path);
};