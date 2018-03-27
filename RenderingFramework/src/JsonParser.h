#pragma once

#include "Light.h"

#include <nlohmann/json.hpp>
#include <glm/glm.hpp>

using json = nlohmann::json;

/*	Automate data loading from json
*/

class JsonParser
{
public:
	static float getFloat(nlohmann::basic_json<> &j);

	static glm::vec3 getVec3(nlohmann::basic_json<> &j);

	static DirectLight getDirectLight(nlohmann::basic_json<> &j);

	static PointLight getPointLight(nlohmann::basic_json<> &j);
};