#version 330 core

#define MAX_POINT_LIGHTS 3

struct Material {
	sampler2D textureDiffuse;
	float shininess;
};

struct DirectionalLight {
	vec3 direction;
	float strength;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight {
	vec3 position;
	float strength;

	float constant;
	float liniear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 Pos;
in vec2 TexCoord;
in vec3 Normal;

in vec3 FragPos;

out vec4 FragColor;

//uniform sampler2D colorTexture;
//uniform sampler2D specTexture;
uniform Material material;
uniform DirectionalLight dirLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];

uniform vec3 Color;

uniform vec3 cameraPos;

uniform bool renderTexture;

vec3 calcDirLight()
{
	vec3 lightDir = normalize(dirLight.direction);
	vec3 viewDir = normalize(cameraPos - FragPos);
	vec3 norm = normalize(Normal);
	float diff = max(dot(norm, -lightDir), 0.0);
    vec3 reflectDir = reflect(lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	return (dirLight.ambient + dirLight.diffuse*diff + dirLight.specular*spec) * dirLight.strength;
}

vec3 calcPointLights()
{
	vec3 normal = normalize(Normal);
	vec3 viewDir = normalize(FragPos - cameraPos);
	vec3 result = vec3(0.0);
	for(int i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		vec3 lightDir = normalize(FragPos - pointLights[i].position);
		vec3 reflectLightDir = reflect(lightDir, normal);
		float dist = distance(FragPos, pointLights[i].position);
		float diffuse = max(dot(-lightDir, normal), 0.0);
		float specular = pow(max(dot(reflectLightDir, -viewDir), 0.0), material.shininess);
		float lightFadeout = 1.0/(pointLights[i].constant + pointLights[i].liniear*dist + pointLights[i].quadratic*dist*dist);
		vec3 lightColor = (pointLights[i].ambient + 
				pointLights[i].diffuse*diffuse +
				pointLights[i].specular*specular);
		result += lightFadeout * lightColor * pointLights[i].strength;
	}
	return result;
}

void main()
{
	vec4 texel;
	if(!renderTexture)
	{
		texel = vec4(1.0);
	}
	else
		texel = texture(material.textureDiffuse, TexCoord);
	
	vec3 lightingColor = calcPointLights() + calcDirLight();
	vec4 result = texel * Color * vec4(lightingColor, 1.0);
	
	FragColor = result;
}