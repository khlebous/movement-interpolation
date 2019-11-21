#pragma once
#include "..//ImGui/imgui.h"
#include "Simulation.h"

class SimulationGui
{
	std::shared_ptr<Simulation> simulation;
	char progressBuf[32];

public:
	SimulationGui() { }
	~SimulationGui() { }

	void SetSimulation(std::shared_ptr<Simulation> _s) { simulation = _s; }

	void Render();
};
