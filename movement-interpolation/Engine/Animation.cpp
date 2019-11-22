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

void Animation::RecalculateModels(float timePercentage, float intermediateFramesCount)
{
	RecalculateEulerModel(timePercentage, intermediateFramesCount);
	RecalculateQuaternionModel(timePercentage, intermediateFramesCount);
}

void Animation::RecalculateEulerModel(float timePercentage, float intermediateFramesCount)
{
	eModel->current.position = GetPosition(eModel->start.position, eModel->end.position, timePercentage);
	eModel->current.rotation = GetEulerRotation(eModel->start.rotation, eModel->end.rotation, timePercentage);

	eModel->intermediate.resize(intermediateFramesCount);
	for (size_t i = 0; i < intermediateFramesCount; i++)
	{
		float timePercentage = (i + 1.0f) / (intermediateFramesCount + 1.0f);
		eModel->intermediate[i].position = GetPosition(eModel->start.position, eModel->end.position, timePercentage);
		eModel->intermediate[i].rotation = GetEulerRotation(eModel->start.rotation, eModel->end.rotation, timePercentage);
	}
}

void Animation::RecalculateQuaternionModel(float timePercentage, float intermediateFramesCount)
{
	qModel->start.position = eModel->start.position;
	qModel->start.rotation = QuaternionUtils::EulerDegreeToQuaternion(eModel->start.rotation);

	qModel->end.position = eModel->end.position;
	qModel->end.rotation = QuaternionUtils::EulerDegreeToQuaternion(eModel->end.rotation);

	qModel->current.position = eModel->current.position;
	qModel->current.rotation = Lerp(qModel->start.rotation, qModel->end.rotation, timePercentage);

	qModel->intermediate.resize(intermediateFramesCount);
	for (size_t i = 0; i < intermediateFramesCount; i++)
	{
		float timePercentage = (i + 1.0f) / (intermediateFramesCount + 1.0f);
		qModel->intermediate[i].position = eModel->intermediate[i].position;
		qModel->intermediate[i].rotation = Lerp(qModel->start.rotation, qModel->end.rotation, timePercentage);
	}
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
