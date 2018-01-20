#version 330 core

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};

struct Light {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
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

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	float diff = max(dot(norm, lightDir), 0.0);

	// phong lightnig
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));
	vec3 specular = light.specular * spec *vec3(texture(material.specular, TexCoord));
	vec3 emission = vec3(texture(material.emission, TexCoord));
	
	FragColor = vec4((ambient + diffuse + specular + emission), 1.0);
	//FragColor = vec4((ambient + diffuse + specular), 1.0) * mix(texel0, texel1, texel1.a*mixvalue);
}