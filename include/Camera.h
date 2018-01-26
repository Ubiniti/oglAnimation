#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace gle {

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera
{
	float _ratio;
	glm::vec2 _screen;
	float _near = 0.1f;
	float _far = 100.0f;
public:
	float _fov = 45.0f;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Position;
	float Downturn = 3.0f;
	float Speed = 3.5f;
	float Acceleration = 3.0f;
	float Sensitivity = 0.08f;
	float Yaw = -90.0f;
	float Pitch = 0.0f;
	Camera(int width, int height) : _screen(glm::vec2(0, 0)),
		Position(0.0f, 0.0f, 3.0f),
		Front(0.0f, 0.0f, -1.0f),
		Up(0.0f, 1.0f, 0.0f),
		_ratio((float)(width / height))
	{}
	glm::mat4 getProjectionMatrix()
	{
		return glm::perspective(glm::radians(_fov), _ratio, _near, _far);
	}
	glm::mat4 getViewMatrix()
	{
		glm::mat4 view(1.0f);
		view = glm::translate(view, -Position);

		view = glm::lookAt(Position, Position + Front, Up);
		return view;
	}
	void ProcessKeyboard(Camera_Movement direction, bool shift, bool space, float deltaTime)
	{
		float movementEffectiveness = (shift ? Acceleration : space ? 1/Downturn : 1.0f);
		switch (direction)
		{
		case FORWARD:
			Position += Speed * Front * deltaTime * movementEffectiveness;
			break;
		case BACKWARD:
			Position -= Speed * Front * deltaTime * movementEffectiveness;
			break;
		case LEFT:
			Position -= glm::normalize(glm::cross(Front, Up)) * Speed * deltaTime * movementEffectiveness;
			break;
		case RIGHT:
			Position += glm::normalize(glm::cross(Front, Up)) * Speed * deltaTime * movementEffectiveness;
			break;
		default:
			break;
		}
	}
	void ProcessMouseMovement(float xoffset, float yoffset)
	{
		Yaw += xoffset * Sensitivity;
		Pitch = glm::max(glm::min(Pitch - yoffset * Sensitivity, 89.0f), -89.0f);
		Front.x = cos(glm::radians(Pitch)) * cos(glm::radians(Yaw));
		Front.y = sin(glm::radians(Pitch));
		Front.z = cos(glm::radians(Pitch)) * sin(glm::radians(Yaw));
		Front = glm::normalize(Front);
	}
	void ProcessMouseScroll(float offset)
	{
		_fov -= offset * 2;
		_fov = glm::max(_fov, 1.0f);
		_fov = glm::min(_fov, 90.0f);
	}
private:
};

}