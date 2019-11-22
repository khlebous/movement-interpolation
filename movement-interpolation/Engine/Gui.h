#pragma once
#include <memory>
#include "..//ImGui/imgui.h"

#include "CameraGui.h"
#include "AnimationGui.h"

class Gui
{
	std::shared_ptr<CameraGui> cameraGui;
	std::shared_ptr<AnimationGui> animationGui;
	bool* showInspector = NULL;

public:
	void SetCameraGui(std::shared_ptr<CameraGui> _cg) { cameraGui = _cg; }
	void SetAnimationGui(std::shared_ptr<AnimationGui> _sg) { animationGui = _sg; }

	void Render();
};
