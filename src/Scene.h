#pragma once

#include "Light.h"
#include "Model.h"

#include "JsonParser.h"

#include <vector>
#include <fstream>
#include <sstream>
#include <string>

#define MAX_POINT_LIGHTS 3

std::ostream& operator<<(std::ostream& stream, glm::vec3 v);

std::ostream& operator<<(std::ostream& stream, DirectLight dl);

std::ostream& operator<<(std::ostream& stream, PointLight pl);

class Scene
{
protected:
	DirectLight _dirLight;
	PointLight _pointLights[MAX_POINT_LIGHTS];
	Model* _lampModel;	// model representing pointLights
	std::vector<Model*> _models;
	std::string jsonData;
public:
	Scene(std::string path)
	{
		loadFromFile(path);
	}
	~Scene()
	{
		for (unsigned int i = 0; i < _models.size(); i++)
		{
			delete _models[i];
		}
		delete _lampModel;
	}
	void addModels(Model *models, const int n)
	{
		for(int i = 0; i < n; i++)
			_models.push_back(&models[i]);
	}

	unsigned int modelsCount() const
	{
		return _models.size();
	}

	const Model* getModel(int index) const
	{
		return _models[index];
	}

	void setDirLight(DirectLight light)
	{
		_dirLight = light;
	}

	glm::vec3 getPointLightPosition(unsigned int index) const
	{
		return _pointLights[index].Position;
	}

	void setPointLightPosition(unsigned int index, glm::vec3 position)
	{
		_pointLights[index].Position = position;
	}

	void setPointLights(PointLight* lights);

	void setPointLight(PointLight * light, int index);

	/*	Load lighting data to shader
	*/
	void updateLighting(const Shader & shader3d) const;

	const Model* getLampModel() const { return _lampModel; }
private:
	/*	Load file from json
	*/
	void loadFromFile(std::string path);

	/*	Parse json to Scene
	*/
	void setup(std::string & data);

	/*	Chceck if json string contain valid scene data
	*/
	std::string validateData(std::string data);
};