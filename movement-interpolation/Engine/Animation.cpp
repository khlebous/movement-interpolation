#include "Animation.h"
#include "Utils/QuaternionUtils.h"

Animation::Animation()
{
	isRunning = false;
	animationTime = 3.0f;
	currentTime = 0.0f;
}

void Animation::Update(float deltaTime)
{
	if (!isRunning)
		return;

	currentTime += deltaTime;

	if (currentTime >= animationTime)
	{
		currentTime = animationTime;
		isRunning = false;
	}

	float timePercentage = currentTime / animationTime;
	eModel->current.position = GetPosition(eModel->start.position, eModel->end.position, timePercentage);
	eModel->current.rotation = GetEulerRotation(eModel->start.rotation, eModel->end.rotation, timePercentage);

	qModel->current.position = eModel->current.position;
	qModel->current.rotation = Lerp(qModel->start.rotation, qModel->end.rotation, timePercentage);
}

void Animation::Render(AnimationModelType type)
{
	view->Render(type);
}

void Animation::StartAnimation()
{
	isRunning = true;
	currentTime = 0.0f;
}

void Animation::OnEulerStartRotationChanged()
{
	UpdateEulerCurrentRotation();
	UpdateEulerIntermediateRotations();

	SetQuaternionStartRotation(eModel->start.rotation);
}

void Animation::OnEulerEndRotationChanged()
{
	UpdateEulerCurrentRotation();
	UpdateEulerIntermediateRotations();

	SetQuaternionEndRotation(eModel->end.rotation);
}

void Animation::OnQuaternionStartRotationChanged()
{
	qModel->start.rotation = glm::normalize(qModel->start.rotation);

	UpdateQuaternionCurrentRotation();
	UpdateQuaternionIntermediateRotations();

	SetEulerStartRotation(qModel->start.rotation);
}

void Animation::OnQuaternionEndRotationChanged()
{
	qModel->end.rotation = glm::normalize(qModel->end.rotation);

	UpdateQuaternionCurrentRotation();
	UpdateQuaternionIntermediateRotations();

	SetEulerEndRotation(qModel->end.rotation);
}

void Animation::OnEulerStartPositionChanged()
{
	qModel->start.position = eModel->start.position;

	float timePercentage = currentTime / animationTime;

	UpdateCurrentConfigurations();
	UpdateIntermediateConfigurations();
}

void Animation::OnEulerEndPositionChanged()
{
	qModel->end.position = eModel->end.position;

	UpdateCurrentConfigurations();

	size_t size = eModel->intermediate.size();
	eModel->intermediate.resize(size);
	qModel->intermediate.resize(size);
	UpdateIntermediateConfigurations();
}

void Animation::SetIntermediateFrames(size_t size)
{
	eModel->intermediate.resize(size);
	qModel->intermediate.resize(size);

	UpdateIntermediateConfigurations();
}

void Animation::SetAnimationPercentage(float timePercentage)
{
	currentTime = timePercentage * animationTime;

	UpdateCurrentConfigurations();
}

void Animation::UpdateCurrentConfigurations()
{
	float timePercentage = currentTime / animationTime;

	eModel->current.position = GetPosition(eModel->start.position, eModel->end.position, timePercentage);
	UpdateEulerCurrentRotation();

	qModel->current.position = eModel->current.position;
	UpdateQuaternionCurrentRotation();
}

void Animation::UpdateIntermediateConfigurations()
{
	size_t size = eModel->intermediate.size();
	for (size_t i = 0; i < size; i++)
	{
		float timePercentage = (float)(i + 1) / (size + 1);

		eModel->intermediate[i].position = GetPosition(eModel->start.position, eModel->end.position, timePercentage);
		qModel->intermediate[i].position = eModel->intermediate[i].position;
	}

	UpdateEulerIntermediateRotations();
	UpdateQuaternionIntermediateRotations();
}

void Animation::UpdateEulerCurrentRotation()
{
	eModel->current.rotation = GetEulerRotation(eModel->start.rotation, eModel->end.rotation, currentTime / animationTime);
}

void Animation::UpdateEulerIntermediateRotations()
{
	size_t intermediateFramesCount = eModel->intermediate.size();
	for (size_t i = 0; i < intermediateFramesCount; i++)
	{
		float timePercentage = (i + 1.0f) / (intermediateFramesCount + 1.0f);
		eModel->intermediate[i].rotation = GetEulerRotation(eModel->start.rotation, eModel->end.rotation, timePercentage);
	}
}

void Animation::UpdateQuaternionCurrentRotation()
{
	qModel->current.rotation = Lerp(qModel->start.rotation, qModel->end.rotation, currentTime / animationTime);
}

void Animation::UpdateQuaternionIntermediateRotations()
{
	size_t intermediateFramesCount = qModel->intermediate.size();
	for (size_t i = 0; i < intermediateFramesCount; i++)
	{
		float timePercentage = (i + 1.0f) / (intermediateFramesCount + 1.0f);
		qModel->intermediate[i].rotation = Lerp(qModel->start.rotation, qModel->end.rotation, timePercentage);
	}
}

void Animation::SetQuaternionEndRotation(glm::vec3 e)
{
	qModel->end.rotation = QuaternionUtils::EulerDegreeToQuaternion(e);

	UpdateQuaternionCurrentRotation();
	UpdateQuaternionIntermediateRotations();
}

void Animation::SetQuaternionStartRotation(glm::vec3 e)
{
	qModel->start.rotation = QuaternionUtils::EulerDegreeToQuaternion(e);

	UpdateQuaternionCurrentRotation();
	UpdateQuaternionIntermediateRotations();
}

void Animation::SetEulerStartRotation(glm::quat q)
{
	glm::vec3 eRotation = glm::degrees(glm::eulerAngles(q));
	eModel->start.rotation = glm::vec3(eRotation.y, eRotation.x, eRotation.z);

	UpdateEulerCurrentRotation();
	UpdateEulerIntermediateRotations();
}

void Animation::SetEulerEndRotation(glm::quat q)
{
	glm::vec3 eRotation = glm::degrees(glm::eulerAngles(q));
	eModel->end.rotation = glm::vec3(eRotation.y, eRotation.x, eRotation.z);

	UpdateEulerCurrentRotation();
	UpdateEulerIntermediateRotations();
}

glm::vec3 Animation::GetPosition(glm::vec3 startPos, glm::vec3 endPos, float timePercentage)
{
	return (endPos - startPos) * timePercentage + startPos;
}

glm::vec3 Animation::GetEulerRotation(glm::vec3 startRot, glm::vec3 endRot, float timePercentage)
{
	return (endRot - startRot) * timePercentage + startRot;
}

glm::quat Animation::Lerp(glm::quat startRot, glm::quat endRot, float timePercentage)
{
	return glm::lerp(startRot, endRot, timePercentage);
}

glm::quat Animation::Slerp(glm::quat startRot, glm::quat endRot, float timePercentage)
{
	return glm::slerp(startRot, endRot, timePercentage);

}
