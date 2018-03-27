#include "Scene.h"

void Scene::setPointLights(PointLight * lights)
{
	for (int i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		_pointLights[i] = lights[i];
	}
}

void Scene::setPointLight(PointLight * light, int index)
{
	_pointLights[index] = *light;
}

void Scene::updateLighting(const Shader & shader3d) const
{
	shader3d.setDirLight("dirLight", _dirLight);
	for (int i = 0; i < MAX_POINT_LIGHTS; i++)
		shader3d.setPointLight("pointLights", i, _pointLights[i]);
}

void Scene::loadFromFile(std::string path)
{
	std::fstream file;
	file.open(path.c_str(), std::ios::in);
	if (!file.is_open())
	{
		std::cout << "[RF:Scene] Failed to load scene from " << path << std::endl;
		return;
	}
	std::string output;
	std::string line;
	while (std::getline(file, line))
	{
		output += line + '\n';
	}

	file.close();
	
	jsonData = output;
	setup(output);
}

void Scene::setup(std::string & data)
{
	//std::cout << data << std::endl;
	std::stringstream parsingLog("");

	auto j = json::parse(data);

	std::string errorLog = validateData(data);
	if (!errorLog.empty())
	{
		std::cout << errorLog << std::endl;
		return;
	}

	// direct light loading
	_dirLight = JsonParser::getDirectLight(j["dirLight"]);
	// point light loading
	unsigned int pointLightsSize = std::min(j["pointLights"].size(), (size_t)MAX_POINT_LIGHTS);
	PointLight* pointLights = new PointLight[pointLightsSize];
	for (unsigned int i = 0; i < pointLightsSize; i++)
	{
		pointLights[i] = JsonParser::getPointLight(j["pointLights"].at(i));
	}
	setPointLights(pointLights);
	// models loading
	// TODO: refactor
	unsigned int modelsCount = j["models"].size();
	for (unsigned int i = 0; i < modelsCount; i++)
	{
		glm::vec3 position, rotation, scale, color;
		std::string modelPath, texturePath;
		position = JsonParser::getVec3(j["models"].at(i)["position"]);
		rotation = JsonParser::getVec3(j["models"].at(i)["rotation"]);
		scale = JsonParser::getVec3(j["models"].at(i)["scale"]);
		color = JsonParser::getVec3(j["models"].at(i)["color"]);
		modelPath = j["models"].at(i)["modelPath"].get<std::string>();
		texturePath = j["models"].at(i)["texturePath"].get<std::string>();
		color.x /= 255.0f;
		color.y /= 255.0f;
		color.z /= 255.0f;

		Model* model = new Model(modelPath, texturePath, rotation);
		model->Position = position;
		model->Scale = scale;
		model->Color = color;
		addModels(model, 1);
	}
	// lamp model loading
	glm::vec3 color, scale, rotation;
	std::string lampPath;
	rotation = JsonParser::getVec3(j["lampModel"]["rotation"]);
	color = JsonParser::getVec3(j["lampModel"]["color"]);
	color.x /= 255.0f;
	color.y /= 255.0f;
	color.z /= 255.0f;
	scale = JsonParser::getVec3(j["lampModel"]["scale"]);
	lampPath = j["lampModel"]["modelPath"].get<std::string>();

	_lampModel = new Model(lampPath, rotation);
	_lampModel->Scale = scale;
	_lampModel->Color = color;

	return;
}

std::string Scene::validateData(std::string data)
{
	std::stringstream parsingLog("");
	auto j = json::parse(data);
	if (j["dirLight"].is_object())
	{
		auto& dirLightP = j["dirLight"];
		std::vector<std::string> members = { "direction", "ambient", "diffuse", "specular" };
		for (std::string member : members)
		{
			if (dirLightP[member].is_array() && dirLightP[member].size() == 3)
			{
				if (!dirLightP[member].at(0).is_number() ||
					!dirLightP[member].at(1).is_number() ||
					!dirLightP[member].at(2).is_number())
				{
					parsingLog << "[RF:Scene:Json] dirLight/" << member << " contains not only numbers!\n";
				}
			}
			else
				parsingLog << "[RF:Scene:Json] dirLight/" << member << " is not an array of size 3!\n";
		}
		if (!dirLightP["strength"].is_number())
		{
			parsingLog << "[RF:Scene:Json] dirLight/strength is not a number!\n";
		}

	}
	else
		parsingLog << "[RF:Scene:Json] dirLight is not an object!\n";

	return parsingLog.str();
}