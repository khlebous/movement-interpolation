#pragma once
#include <memory>
#include "CameraGui.h"
#include "..//ImGui/imgui.h"

class Gui
{
	std::shared_ptr<CameraGui> cameraGui;
	bool* showInspector = NULL;

public:
	Gui() { }

	void SetCameraGui(std::shared_ptr<CameraGui> _cg) { cameraGui = _cg; }
	void Render();
};