#pragma once

#include "Axes.h"
#include "SimulationModel.h"

class SimulationView
{
	std::shared_ptr<SimulationModel<glm::vec3>> model;
	std::shared_ptr<Axes> gameObject;

public:
	SimulationView() { }
	~SimulationView() { }

	void SetGameObject(std::shared_ptr<Axes> _go) { gameObject = _go; }
	void SetSimulationEulerModel(std::shared_ptr<SimulationModel<glm::vec3>> _sm) { model = _sm; }

	void Render();
};
