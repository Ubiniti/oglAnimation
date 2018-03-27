#include "Camera.h"
#include <iostream>

Camera::Camera(const glm::vec3 position, float ratio) :
	Sensitivity(10.0f),
	_position(position),
	_ratio(ratio),
	_fov(45.0f),
	_near(0.1f),
	_far(100.0f),
	_view(1.0f),
	_projection(1.0f),
	_front(glm::vec3(0.0f, 0.0f, 0.0f)),
	_up(glm::vec3(0.0f, 1.0f, 0.0f)),
	_pitch(0.0f),
	_yaw(-90.0f)
{	
	updateView();
	updateProjection();
}

glm::mat4 Camera::getViewMatrix() const
{
	return _view;
}

glm::mat4 Camera::getProjectionMatrix() const
{
	return _projection;
}

void Camera::setPosition(glm::vec3 position)
{
	_position = position;
	updateView();
}

glm::vec3 Camera::getPosition() const
{
	return _position;
}

void Camera::move(CameraMovement direction, float speed)
{
	glm::mat4 transformMat(1.0);
	switch (direction)
	{
	case FORWARD:
		_position += _front * speed;
		break;
	case BACKWARD:
		_position -= _front * speed;
		break;
	case LEFT:
		_position -= glm::normalize(glm::cross(_front, _up)) * speed;
		break;
	case RIGHT:
		_position += glm::normalize(glm::cross(_front, _up)) * speed;
		break;
	default:
		break;
	}

	updateView();
}

void Camera::rotate(float xoffset, float yoffset)
{
	_yaw += xoffset * Sensitivity;
	_pitch = glm::max(glm::min(_pitch - yoffset * Sensitivity, 89.0f), -89.0f);

	updateView();
}

void Camera::updateView()
{
	_front.x = cos(glm::radians(_pitch)) * cos(glm::radians(_yaw));
	_front.y = sin(glm::radians(_pitch));
	_front.z = cos(glm::radians(_pitch)) * sin(glm::radians(_yaw));
	_front = glm::normalize(_front);

	_view = glm::mat4(1.0f);
	_view = glm::translate(_view, -_position);
	_view = glm::lookAt(_position, _position + _front, _up);
}

void Camera::updateProjection()
{
	_projection = glm::perspective(glm::radians(_fov), _ratio, _near, _far);
}
