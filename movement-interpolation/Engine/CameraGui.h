#pragma once
#include <memory>
#include "Camera.h"
#include "..//ImGui/imgui.h"

class CameraGui
{
	std::shared_ptr<Camera> camera;

public:
	CameraGui() { }

	void SetCamera(std::shared_ptr<Camera> _c) { camera = _c; }
	void Render();
};