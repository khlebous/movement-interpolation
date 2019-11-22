#include "SimulationView.h"

void SimulationView::Render()
{
	gameObject->Render(model->currPos, model->currRot, 1.0f);

	gameObject->Render(model->startPos, model->startRot, 0.3f);
	gameObject->Render(model->endPos, model->endRot, 0.3f);
}
