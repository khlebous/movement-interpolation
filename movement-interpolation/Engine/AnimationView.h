#pragma once
#include <glm/glm.hpp>

#include "Axes.h"
#include "AnimationModel.h"
#include "AnimationModelType.h"

class AnimationView
{
	std::shared_ptr<AnimationModel<glm::vec3>> eulerModel;
	std::shared_ptr<AnimationModel<glm::quat>> quatModel;
	std::shared_ptr<Axes> gameObject;

public:
	AnimationView() { }
	~AnimationView() { }

	void SetGameObject(std::shared_ptr<Axes> _go) { gameObject = _go; }
	void SetAnimationEulerModel(std::shared_ptr<AnimationModel<glm::vec3>> _sm) { eulerModel = _sm; }
	void SetAnimationQuatModel(std::shared_ptr<AnimationModel<glm::quat>> _sm) { quatModel = _sm; }

	void Render(AnimationModelType type);

private:
	void RenderEuler();
	void RenderQuaternion();

	glm::mat4 GetEulerModelMatrix(const Configuration<glm::vec3>& configuration);
	glm::mat4 GetQaternionModelMatrix(const Configuration<glm::quat>& configuration);
};
