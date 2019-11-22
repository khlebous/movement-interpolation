#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <memory>

class SimulationModel
{
public:
	glm::vec3 startPos;
	glm::vec3 startRot;
	glm::vec3 endPos;
	glm::vec3 endRot;
	glm::vec3 currPos;
	glm::vec3 currRot;

	bool isRunning;
	float animationTime;
	float currentTime;

	SimulationModel();
	~SimulationModel() { }
};
