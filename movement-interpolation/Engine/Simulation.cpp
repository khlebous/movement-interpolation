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
