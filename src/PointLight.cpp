#include "PointLight.h"

namespace gle
{
	int PointLight::count = 0;

	bool PointLight::slots[4] = {false, false, false, false};

	void PointLight::upload(Shader shader)
	{
		if (id == -1)
		{
			for (int i = 0; i < 4; i++)
			{
				if (!slots[i])
				{
					slots[i] = true;
					id = count++;
					break;
				}
			}
		}
		if (id != -1)
		{
			shader.setVec3(("pointLights[" + std::to_string(id) + "].position").c_str(), Position);
			shader.setVec3(("pointLights[" + std::to_string(id) + "].ambient").c_str(), ambient);
			shader.setVec3(("pointLights[" + std::to_string(id) + "].diffuse").c_str(), diffuse);
			shader.setVec3(("pointLights[" + std::to_string(id) + "].specular").c_str(), specular);
			shader.setFloat(("pointLights[" + std::to_string(id) + "].constant").c_str(), constant);
			shader.setFloat(("pointLights[" + std::to_string(id) + "].linear").c_str(), linear);
			shader.setFloat(("pointLights[" + std::to_string(id) + "].quadratic").c_str(), quadratic);
		}
		std::cout << std::to_string(id) << std::endl;
	}
}