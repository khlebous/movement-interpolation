#pragma once
#include "..//ImGui/imgui.h"
#include "Animation.h"

class AnimationGui
{
	std::shared_ptr<Animation> animation;
	float animationPercentage;
	int intermediateFramesCount;

public:
	AnimationGui();
	~AnimationGui() { }

	void SetAnimation(std::shared_ptr<Animation> _a) { animation = _a; }

	void Render();

private:
	void PushDisabled();
	void PopDisabled();
};
