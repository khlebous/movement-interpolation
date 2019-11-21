#pragma once

#include "SimulationView.h"

class Simulation
{
	std::shared_ptr<SimulationModel> model;
	std::shared_ptr<SimulationView> view;

public:
	void SetModel(std::shared_ptr<SimulationModel> _m) { model = _m; }
	void SetView(std::shared_ptr<SimulationView> _v) { view = _v; }

	std::shared_ptr<SimulationModel> GetModel() { return model; }

	void Update(float deltaTime);
	void Render();

	void StartAnimation();
};
