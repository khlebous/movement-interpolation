#define GLM_ENABLE_EXPERIMENTAL 

#include "AnimationView.h"
#include "VectorConstants.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

void AnimationView::Render(AnimationModelType type)
{
	switch (type)
	{
	case EULER:	RenderEuler(); break;
	case QUATERNION: RenderQuaternion(); break;
	default: break;
	}
}

void AnimationView::RenderEuler()
{
	gameObject->Render(GetEulerModelMatrix(eulerModel->current), 1.0f);
	gameObject->Render(GetEulerModelMatrix(eulerModel->start), 0.7f);
	gameObject->Render(GetEulerModelMatrix(eulerModel->end), 0.7f);

	for (size_t i = 0; i < eulerModel->intermediate.size(); i++)
	{
		gameObject->Render(GetEulerModelMatrix(eulerModel->intermediate[i]), 0.4f);
	}
}

void AnimationView::RenderQuaternion()
{
	gameObject->Render(GetQaternionModelMatrix(quatModel->current), 1.0f);
	gameObject->Render(GetQaternionModelMatrix(quatModel->start), 0.7f);
	gameObject->Render(GetQaternionModelMatrix(quatModel->end), 0.7f);

	for (size_t i = 0; i < quatModel->intermediate.size(); i++)
	{
		gameObject->Render(GetQaternionModelMatrix(quatModel->intermediate[i]), 0.4f);
	}
}

glm::mat4 AnimationView::GetEulerModelMatrix(const Configuration<glm::vec3>& configuration)
{
	glm::mat4 m_model = glm::translate(glm::mat4(1), configuration.position);

	m_model = glm::rotate(m_model, glm::radians(configuration.rotation.z), VectorConstants::V_FORWARD);
	m_model = glm::rotate(m_model, glm::radians(configuration.rotation.x), VectorConstants::V_UP);
	m_model = glm::rotate(m_model, glm::radians(configuration.rotation.y), VectorConstants::V_RIGHT);
	
	return m_model;
}

glm::mat4 AnimationView::GetQaternionModelMatrix(const Configuration<glm::quat>& configuration)
{
	glm::mat4 m_model = glm::translate(glm::mat4(1), configuration.position);
	m_model = m_model * glm::toMat4(configuration.rotation);

	return m_model;
}
