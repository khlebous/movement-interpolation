#pragma once
#include "AnimationView.h"
#include "Utils/QuaternionUtils.h"

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

	std::shared_ptr<AnimationModel<glm::vec3>> GetEulerModel() { return eModel; }
	std::shared_ptr<AnimationModel<glm::quat>> GetQuaternionModel() { return qModel; }

	void Update(float deltaTime);
	void Render(AnimationModelType type);

	void StartAnimation();

	void OnEulerStartRotationChanged();
	void OnEulerEndRotationChanged();
	void OnQuaternionStartRotationChanged();
	void OnQuaternionEndRotationChanged();

	void OnEulerStartPositionChanged();
	void OnEulerEndPositionChanged();
	void SetIntermediateFrames(size_t size);
	void SetAnimationPercentage(float timePercentage);

private:
	void UpdateCurrentConfigurations();
	void UpdateIntermediateConfigurations();
	void UpdateEulerCurrentRotation();
	void UpdateEulerIntermediateRotations();
	void UpdateQuaternionCurrentRotation();
	void UpdateQuaternionIntermediateRotations();

	void SetQuaternionEndRotation(glm::vec3 e);
	void SetQuaternionStartRotation(glm::vec3 e);
	void SetEulerStartRotation(glm::quat q);
	void SetEulerEndRotation(glm::quat q);

	glm::vec3 GetPosition(glm::vec3 startPos, glm::vec3 endPos, float timePercentage);
	glm::vec3 GetEulerRotation(glm::vec3 startRot, glm::vec3 endRot, float timePercentage);
	glm::quat Lerp(glm::quat startRot, glm::quat endRot, float timePercentage);
	glm::quat Slerp(glm::quat startRot, glm::quat endRot, float timePercentage);
};
