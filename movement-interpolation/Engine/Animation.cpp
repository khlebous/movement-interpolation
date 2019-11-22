#include "Animation.h"

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
	eModel->current.position = (eModel->end.position - eModel->start.position) * timePercentage + eModel->start.position;
	eModel->current.rotation = (eModel->end.rotation - eModel->start.rotation) * timePercentage + eModel->start.rotation;
}

void Animation::Render()
{
	view->Render();
}

void Animation::StartAnimation()
{
	isRunning = true;
	currentTime = 0.0f;
}

void Animation::RecalculateConfiguration(float timePercentage, float intermediateFramesCount)
{
	eModel->current.position = (eModel->end.position - eModel->start.position) * timePercentage + eModel->start.position;
	eModel->current.rotation = (eModel->end.rotation - eModel->start.rotation) * timePercentage + eModel->start.rotation;

	eModel->intermediate.resize(intermediateFramesCount);

	for (size_t i = 0; i < intermediateFramesCount; i++)
	{
		float timePercentage = (i + 1.0f) / (intermediateFramesCount + 1.0f);
		eModel->intermediate[i].position = (eModel->end.position - eModel->start.position) * timePercentage + eModel->start.position;
		eModel->intermediate[i].rotation = (eModel->end.rotation - eModel->start.rotation) * timePercentage + eModel->start.rotation;
	}
}
