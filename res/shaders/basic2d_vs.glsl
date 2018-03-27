#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 pos;
out vec2 texCoord;

uniform vec2 pos2d;
uniform vec2 scale2d;

void main()
{
	vec2 outPos = aPos * scale2d;
	gl_Position = vec4(outPos + pos2d, -1.0, 1.0);
	pos = outPos;
	texCoord = aTexCoord;
}