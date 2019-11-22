#pragma once
#include "..//ImGui/imgui.h"
#include "Simulation.h"

class SimulationGui
{
	std::shared_ptr<Simulation> simulation;
	float animationPercentage;
	int intermediateFramesCount;

public:
	SimulationGui();
	~SimulationGui() { }

	void SetSimulation(std::shared_ptr<Simulation> _s) { simulation = _s; }

	void Render();

private:
	void PushDisabled();
	void PopDisabled();
};
