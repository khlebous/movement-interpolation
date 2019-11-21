#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <memory>

class SimulationModel
{
public:
	glm::vec3 startPos;
	glm::vec3 endPos;
	glm::vec3 currPos;

	bool isRunning;
	float animationTime;
	float currentTime;

	SimulationModel();
	~SimulationModel() { }
};
