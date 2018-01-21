#version 330 core

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};

struct Light {
	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

uniform Material material;
uniform Light light;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixvalue;

uniform vec3 viewPos;

uniform float time;

void main()
{
	vec4 texel0 = texture(texture1, TexCoord);
	vec4 texel1 = texture(texture2, TexCoord);

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	//vec3 lightDir = normalize(-light.direction);

	vec3 viewDir = (normalize(viewPos - FragPos));
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	float diff = max(dot(norm, lightDir), 0.0);

	// attenuation calculations for point light and spotlight
	float distance = length(light.position - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear*distance +
						light.quadratic*(distance*distance) );

	

	vec4 resultColor;

	float theta = dot(lightDir, normalize(-light.direction));

	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));
	ambient *= attenuation;
	
	if(theta > light.outerCutOff)
	{
		// phong lightnig
		vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));
		vec3 specular = light.specular * spec *vec3(texture(material.specular, TexCoord));
		vec3 emission = vec3(texture(material.emission, TexCoord));

		float epsilon   = light.cutOff - light.outerCutOff;
		float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

		diffuse *= attenuation * intensity;
		specular *= attenuation * intensity;
		
		resultColor = vec4(ambient + diffuse + specular, 1.0);
	}
	else
		resultColor = vec4(ambient, 1.0);
	
	FragColor = resultColor;
	//FragColor = vec4((ambient + diffuse + specular), 1.0) * mix(texel0, texel1, texel1.a*mixvalue);
}