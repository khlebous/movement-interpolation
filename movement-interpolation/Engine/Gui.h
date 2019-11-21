#pragma once
#include <memory>
#include "..//ImGui/imgui.h"

#include "CameraGui.h"
#include "SimulationGui.h"

class Gui
{
	std::shared_ptr<CameraGui> cameraGui;
	std::shared_ptr<SimulationGui> simulationGui;
	bool* showInspector = NULL;

public:
	void SetCameraGui(std::shared_ptr<CameraGui> _cg) { cameraGui = _cg; }
	void SetSimulationGui(std::shared_ptr<SimulationGui> _sg) { simulationGui = _sg; }

	void Render();
};
