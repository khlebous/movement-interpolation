#include "Simulation.h"

void Simulation::Update(float deltaTime)
{
	if (!model->isRunning)
		return;

	model->currentTime += deltaTime;

	if (model->currentTime >= model->animationTime)
	{
		model->currentTime = model->animationTime;
		model->isRunning = false;
	}

	SetCurrentPosition(model->currentTime / model->animationTime);
}

void Simulation::Render()
{
	view->Render();
}

void Simulation::StartAnimation()
{
	model->isRunning = true;
	model->currentTime = 0.0f;
}

void Simulation::SetCurrentPosition(float timePercentage)
{
	model->currPos = (model->endPos - model->startPos) * timePercentage + model->startPos;
	model->currRot = (model->endRot - model->startRot) * timePercentage + model->startRot;
}
