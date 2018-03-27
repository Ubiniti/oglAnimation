#include "Model.h"

void Model::printLinkedTextures(const aiScene* scene) const
{
	const unsigned int texture_types_number = 11;
	int sum = 0;
	auto matCount = scene->mNumMaterials;
	for (unsigned int k = 0; k < matCount; k++)
	{
		for (int i = 1; i <= texture_types_number; i++)
		{
			auto count = scene->mMaterials[k]->GetTextureCount((aiTextureType)i);
			for (unsigned int j = 0; j < count; j++)
			{
				aiString texpath;
				scene->mMaterials[k]->GetTexture((aiTextureType)i, j, &texpath);
				std::cout << "(" << i << ") texpath: " << texpath.C_Str() << std::endl;
			}
		}
	}
}
void Model::draw(const Shader & shader) const
{
	shader.use();
	for (unsigned int i = 0; i < _meshes.size(); i++)
	{
		shader.setBool("renderTexture", _meshes.at(i).isTextured());
		_meshes.at(i).draw();
	}
}

bool Model::empty()
{
	return _meshes.size() == 0;
}

bool Model::isTextured()
{
	return _textures.size() > 0;
}

std::string Model::getTexturePath(const aiMaterial* material, aiTextureType type)
{
	aiString path;
	// assume there is only one diffuse texture per mesh
	if (material->GetTextureCount(type) > 0)
	{
		material->GetTexture(type, 0, &path);
	}
	return std::string(path.C_Str());
}

Texture Model::loadTexture(const aiScene* scene, const aiMaterial* material)
{
	Texture texture;
	std::string diffusePath = getTexturePath(material, aiTextureType_DIFFUSE);
	//std::cout << "Loading: " << diffusePath << std::endl;
	// check if found textures were loaded before
	std::string diffuseFullPath = _directory + '/' + diffusePath.c_str();
	for (unsigned int i = 0; i < _textures.size(); i++)
	{
		if (std::strcmp(_textures[i].getPath(), diffuseFullPath.c_str()) == 0)
		{
			texture = _textures[i];
		}
	}
	// texture was not loaded && texture was found linked to the model
	// then load from file
	if (texture.Blank() && !diffusePath.empty())
	{
		texture = Texture(diffuseFullPath.c_str(), true);
		_textures.emplace_back(texture);
		//std::cout << "(diffuse) texpath: " << diffuseFullPath.c_str() << std::endl;
	}
	return texture;
}

Mesh Model::loadMesh(const aiScene* scene, const aiMesh *mesh)
{
	// calulating rotation matrix
	glm::mat4 rotationMatrix(1.0f);
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(_initRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(_initRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(_initRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	// --------------------
	unsigned int count = mesh->mNumVertices;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	vertices.reserve(count);
	indices.reserve(count);
	// indices
	for (unsigned int j = 0; j < mesh->mNumFaces; j++)
	{
		aiFace face = mesh->mFaces[j];
		for (unsigned int k = 0; k < face.mNumIndices; k++)
		{
			indices.push_back(face.mIndices[k]);
		}
	}
	// vertices
	for (unsigned int j = 0; j < count; j++)
	{

		Vertex vertex;
		// position
		glm::vec3 vertPos;
		vertPos.x = mesh->mVertices[j].x;
		vertPos.y = mesh->mVertices[j].y;
		vertPos.z = mesh->mVertices[j].z;
		vertex.Position = rotationMatrix * glm::vec4(vertPos, 1.0f);
		// tex-coord
		if (mesh->mTextureCoords[0])
		{
			glm::vec2 texcoord;
			texcoord.x = mesh->mTextureCoords[0][j].x;
			texcoord.y = mesh->mTextureCoords[0][j].y;
			vertex.TexCoords = texcoord;
		}
		else
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		// normal
		glm::vec3 normal;
		normal.x = mesh->mNormals[j].x;
		normal.y = mesh->mNormals[j].y;
		normal.z = mesh->mNormals[j].z;
		vertex.Normal = rotationMatrix * glm::vec4(normal, 1.0f);
		vertices.push_back(vertex);
	}
	// textures
	aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
	Texture texture = loadTexture(scene, material);

	return Mesh(vertices, indices, texture);
}

void Model::loadFromFile(std::string path)
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene)
	{
		std::cout << "[Assimp] error: couldn't load file from " << path << std::endl;
	}
	else
	{
		_directory = path.substr(0, path.find_last_of('/'));

		//printLinkedTextures(scene);
		//load meshes
		for (unsigned int i = 0; i < scene->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[i];

			_meshes.emplace_back(loadMesh(scene, mesh));
		}
	}
}