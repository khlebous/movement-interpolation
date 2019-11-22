#pragma once

#include "Axes.h"
#include "AnimationModel.h"

class AnimationView
{
	std::shared_ptr<AnimationModel<glm::vec3>> model;
	std::shared_ptr<Axes> gameObject;

public:
	AnimationView() { }
	~AnimationView() { }

	void SetGameObject(std::shared_ptr<Axes> _go) { gameObject = _go; }
	void SetAnimationEulerModel(std::shared_ptr<AnimationModel<glm::vec3>> _sm) { model = _sm; }

	void Render();
};
