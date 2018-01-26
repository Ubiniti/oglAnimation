#pragma once

#include "Color.h"
#include "Shader.h"

#include <glm/glm.hpp>

namespace gle
{

	class Light
	{
	protected:
		enum LightType {
			Point,
			Spot,
			Directional
		};
		LightType type;
		Light(LightType type, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) :
			Light(ambient, diffuse, specular)
		{
			this->type = type;
		}
	public:
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) :
			ambient(ambient),
			diffuse(diffuse),
			specular(specular)
		{}
		virtual void upload(Shader shader) = 0;
	};

} // gle