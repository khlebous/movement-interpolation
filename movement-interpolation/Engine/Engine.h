#pragma once
#include <memory>

#include "Axes.h"
#include "Camera.h"
#include "Shader.h"
#include "Gui.h"

class Engine
{
	std::shared_ptr<Axes> axes;
	std::shared_ptr<Camera> camera;
	std::shared_ptr<Shader> shader;
	std::shared_ptr<Gui> gui;

public:
	Engine();

	std::shared_ptr<Camera> GetCamera() { return camera; }

	void Render(float deltaTime);
	void RenderGui();

private:
	void UpdateCameraMatrices();
	void UpdateShader();
};