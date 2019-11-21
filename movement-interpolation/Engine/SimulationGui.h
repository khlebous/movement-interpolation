#pragma once
#include "..//ImGui/imgui.h"
#include "SimulationModel.h"

class SimulationGui
{
	std::shared_ptr<SimulationModel> model;

public:
	SimulationGui() { }
	~SimulationGui() { }

	void SetModel(std::shared_ptr<SimulationModel> _sm) { model = _sm; }

	void Render();
};
