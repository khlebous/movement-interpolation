#include "Camera.h"

Camera::Camera(glm::vec3 _pos, float _yaw, float _pitch, glm::vec3 _worldUp, glm::vec3 _front) :
	Position(_pos), Yaw(_yaw), Pitch(_pitch), worldUp(_worldUp), front(_front),
	MovementSpeed(10.0f), MouseSensitivity(0.1f), Zoom(45.0f),
	Near(1.0f), Far(100.0f),
	maxPitch(89.0f), minZoom(1.0f), maxZoom(45.0f)
{
	UpdateCameraVectors();
}

void Camera::ProcessKeyboard(MovementDirection direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;

	switch (direction)
	{
	case FORWARD:Position += front * velocity; break;
	case BACKWARD:Position -= front * velocity; break;
	case LEFT:Position -= right * velocity;	break;
	case RIGHT:	Position += right * velocity; break;
	case UP:Position.y += velocity; break;
	case DOWN:Position.y -= velocity; break;
	default:break;
	}
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	if (Pitch > maxPitch) Pitch = maxPitch;
	if (Pitch < -maxPitch) Pitch = -maxPitch;

	UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
	if (Zoom >= minZoom && Zoom <= maxZoom)
		Zoom -= yoffset;

	if (Zoom <= minZoom) Zoom = minZoom;
	if (Zoom >= maxZoom) Zoom = maxZoom;
}

void Camera::UpdateViewMatrix()
{
	View = glm::lookAt(Position, Position + front, up);
}

void Camera::UpdateProjectionMatrix()
{
	Projection = glm::perspective(glm::radians(Zoom), (float)WindowConstants::WIDTH / ((float)WindowConstants::HEIGHT / 2.0f), 1.0f, 100.0f);
}

void Camera::UpdateCameraVectors()
{
	// Calculate the new Front vector
	front = glm::normalize(glm::vec3(
		cos(glm::radians(Yaw)) * cos(glm::radians(Pitch)),
		sin(glm::radians(Pitch)),
		sin(glm::radians(Yaw)) * cos(glm::radians(Pitch))));
	// Also re-calculate the Right and Up vector
	right = glm::normalize(glm::cross(front, worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	up = glm::normalize(glm::cross(right, front));
}
