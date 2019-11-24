#pragma once
#include "..//ImGui/imgui.h"
#include "Animation.h"

class AnimationGui
{
	std::shared_ptr<Animation> animation;
	float animationPercentage;
	int intermediateFramesCount;

	bool* showEuler = NULL;
	bool* showQuaternion = NULL;

public:
	AnimationGui();
	~AnimationGui() 
	{
		delete showEuler;
		delete showQuaternion;
	}

	void SetAnimation(std::shared_ptr<Animation> _a) { animation = _a; }

	void RenderMenu();
	void Render();

private:
	void PushDisabled();
	void PopDisabled();

	void RenderEulerWindow();
	void RenderQuaternionWindow();
};
