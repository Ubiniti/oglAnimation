#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum CameraMovement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

/*	Allows for getting around the 3D space
	and calculates view and projection matrices
*/
class Camera
{
	float _ratio;
	float _fov; // field of view
	float _near;// drawing distance
	float _far;	// -,,-
	glm::vec3 _position;
	glm::mat4 _view;
	glm::mat4 _projection;
	glm::vec3 _front;
	glm::vec3 _up;
	float _pitch;
	float _yaw;
public:
	float Sensitivity;
	Camera(const glm::vec3 position, float ratio);
	glm::mat4 getViewMatrix() const;
	glm::mat4 getProjectionMatrix() const;
	void setPosition(glm::vec3 position);
	glm::vec3 getPosition() const;
	void move(CameraMovement direction, float speed);
	void rotate(float xoffset, float yoffset);
private:
	// recalculate view matrix
	void updateView();
	// recalculate projection matrix
	void updateProjection();
};