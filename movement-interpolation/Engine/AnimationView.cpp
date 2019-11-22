#include "AnimationView.h"
#include <glm/gtc/matrix_transform.hpp>

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
	/*m_model = glm::translate(glm::mat4(1), pos);

	m_model = glm::rotate(m_model, glm::radians(rot.x), VectorConstants::V_RIGHT);
	m_model = glm::rotate(m_model, glm::radians(rot.y), VectorConstants::V_UP);
	m_model = glm::rotate(m_model, glm::radians(rot.z), VectorConstants::V_FORWARD);*/

	float rad_x = glm::radians(configuration.rotation.x);
	float s1 = glm::sin(rad_x);
	float c1 = glm::cos(rad_x);
	float rad_y = glm::radians(configuration.rotation.y);
	float s2 = glm::sin(rad_y);
	float c2 = glm::cos(rad_y);
	float rad_z = glm::radians(configuration.rotation.z);
	float s3 = glm::sin(rad_z);
	float c3 = glm::cos(rad_z);

	return glm::transpose(glm::mat4(c2 * c3, -s2, c2 * s3, configuration.position.x,
		s1 * s3 + c1 * c3 * s2, c1 * c2, c1 * s2 * s3 - c3 * s1, configuration.position.y,
		c3 * s1 * s2 - c1 * s3, c2 * s1, c1 * c3 + s1 * s2 * s3, configuration.position.z,
		0, 0, 0, 1));
}

glm::mat4 AnimationView::GetQaternionModelMatrix(const Configuration<glm::quat>& configuration)
{
	return glm::mat4(1);
}
