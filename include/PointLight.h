#pragma once

#include "Light.h"

#include <iostream>

namespace gle
{

	class PointLight : public Light
	{
		int id = -1;
		static bool slots[4];
		static int count;
		float constant = 1.0f;
		float linear = 0.09f;
		float quadratic = 0.032f;
	public:
		glm::vec3 Position;
		PointLight(glm::vec3 position, glm::vec3 ambient = glm::vec3(0.2),
			glm::vec3 diffuse = glm::vec3(0.5),
			glm::vec3 specular = glm::vec3(1.0)) :
				Light(Point, ambient, diffuse, specular),
				Position(position)
		{}
		~PointLight()
		{
			slots[id] = false;
			count--;
		}
		void upload(Shader shader);
	};

} // gle