#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <memory>

class SimulationModel
{
public:
	glm::vec3 startPos;
	glm::vec3 endPos;

	float animationTime;

	SimulationModel() : startPos(glm::vec3(0)), endPos(glm::vec3(0)), animationTime(3) { }
	~SimulationModel() { }

	void Update(float deltaTime) { }
};
