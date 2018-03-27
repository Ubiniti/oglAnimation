#include "JsonParser.h"

float JsonParser::getFloat(nlohmann::basic_json<>& j)
{
	if (j.is_number())
	{
		return j.get<float>();
	}
}

glm::vec3 JsonParser::getVec3(nlohmann::basic_json<>& j)
{
	if (j.is_array() && j.size() == 3)
	{
		if (j.at(0).is_number() &&
			j.at(1).is_number() &&
			j.at(2).is_number())
		{
			return glm::vec3(j.at(0).get<float>(),
				j.at(1).get<float>(),
				j.at(2).get<float>());
		}
	}
	return glm::vec3(0.0);
}

DirectLight JsonParser::getDirectLight(nlohmann::basic_json<>& j)
{
	DirectLight dirLight;
	if (j.is_object() && j.size() == 5)
	{
		dirLight.Direction = getVec3(j["direction"]);
		dirLight.Ambient = getVec3(j["ambient"]);
		dirLight.Diffuse = getVec3(j["diffuse"]);
		dirLight.Specular = getVec3(j["specular"]);
		dirLight.Strength = j["strength"].get<float>();
	}
	return dirLight;
}

PointLight JsonParser::getPointLight(nlohmann::basic_json<>& j)
{
	PointLight pointLight;
	if (j.is_object() && j.size() == 8)
	{
		pointLight.Position = getVec3(j["position"]);
		pointLight.Ambient = getVec3(j["ambient"]);
		pointLight.Diffuse = getVec3(j["diffuse"]);
		pointLight.Specular = getVec3(j["specular"]);
		pointLight.Strength = j["strength"].get<float>();
		pointLight.Constant = j["constant"].get<float>();
		pointLight.Liniear = j["liniear"].get<float>();
		pointLight.Quadratic = j["quadratic"].get<float>();
	}
	return pointLight;
}
