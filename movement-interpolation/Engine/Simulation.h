#pragma once

#include "SimulationView.h"

class Simulation
{
	std::shared_ptr<SimulationModel<glm::vec3>> eModel;
	std::shared_ptr<SimulationView> view;

public:
	bool isRunning;
	float animationTime;
	float currentTime;

	Simulation();

	void SetEulerModel(std::shared_ptr<SimulationModel<glm::vec3>> _m) { eModel = _m; }
	void SetView(std::shared_ptr<SimulationView> _v) { view = _v; }

	std::shared_ptr<SimulationModel<glm::vec3>> GetModel() { return eModel; }

	void Update(float deltaTime);
	void Render();

	void StartAnimation();
	void RecalculateConfiguration(float timePercentage, float intermediateFramesCount);
};
