#pragma once

#include "SimulationView.h"

class Simulation
{
	std::shared_ptr<SimulationModel> model;
	std::shared_ptr<SimulationView> view;

	glm::vec3 startPos;
	glm::vec3 endPos;
	float animationTime;

public:
	void SetModel(std::shared_ptr<SimulationModel> _m) { model = _m; }
	void SetView(std::shared_ptr<SimulationView> _v) { view = _v; }

	void Update(float deltaTime);
	void Render();
};
