#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Constnants/WindowConstants.h"
#include "MovementDirection.h"

// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
	glm::vec3 worldUp;
	glm::vec3 right;
	glm::vec3 up;
	glm::vec3 front;

	// Camera options
	float maxPitch;
	float minZoom, maxZoom;

public:
	glm::vec3 Position;

	// Euler Angles
	float Yaw;
	float Pitch;

	// Mtxs
	glm::mat4 View;
	glm::mat4 Projection;

	// Camera options
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	float Near;
	float Far;


	Camera(glm::vec3 _pos, float _yaw, float _pitch, glm::vec3 _worldUp, glm::vec3 _front); 

	void ProcessKeyboard(MovementDirection direction, float deltaTime);
	void ProcessMouseMovement(float xoffset, float yoffset);
	void ProcessMouseScroll(float yoffset);

	void UpdateViewMatrix();
	void UpdateProjectionMatrix();
	void UpdateCameraVectors();
};
