#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

out vec3 Pos;
out vec2 TexCoord;
out vec3 Normal;

out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 rotation;

void main()
{
	gl_Position = projection * view * model * rotation * vec4(aPos, 1.0);
	FragPos = vec3(model * rotation * vec4(aPos, 1.0));
	Pos = aPos;
	TexCoord = aTexCoord;
	Normal = vec3(rotation * vec4(aNormal, 1.0));
}