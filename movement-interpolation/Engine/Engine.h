#pragma once
#include <memory>

#include "Animation.h"
#include "Camera.h"
#include "Shader.h"
#include "Gui.h"

class Engine
{
	std::shared_ptr<Animation> animation;
	std::shared_ptr<Camera> camera;
	std::shared_ptr<Shader> shader;
	std::shared_ptr<Gui> gui;
	
public:
	Engine();

	std::shared_ptr<Camera> GetCamera() { return camera; }

	void Update(float deltaTime);
	void Render(AnimationModelType type);
	void RenderGui();

private:
	void UpdateCameraMatrices();
	void UpdateShader();
};
