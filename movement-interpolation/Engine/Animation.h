#pragma once
#include "AnimationView.h"

class Animation
{
	std::shared_ptr<AnimationModel<glm::vec3>> eModel;
	std::shared_ptr<AnimationModel<glm::quat>> qModel;
	std::shared_ptr<AnimationView> view;

public:
	bool isRunning;
	float animationTime;
	float currentTime;

	Animation();

	void SetEulerModel(std::shared_ptr<AnimationModel<glm::vec3>> _m) { eModel = _m; }
	void SetQuatModel(std::shared_ptr<AnimationModel<glm::quat>> _m) { qModel = _m; }
	void SetView(std::shared_ptr<AnimationView> _v) { view = _v; }

	std::shared_ptr<AnimationModel<glm::vec3>> GetModel() { return eModel; }

	void Update(float deltaTime);
	void Render(AnimationModelType type);

	void StartAnimation();
	void RecalculateConfiguration(float timePercentage, float intermediateFramesCount);
};
