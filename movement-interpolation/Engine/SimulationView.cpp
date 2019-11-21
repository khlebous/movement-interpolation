#include "SimulationView.h"

void SimulationView::Render()
{
	gameObject->Render(model->currPos, 1.0f);

	gameObject->Render(model->startPos, 0.3f);
	gameObject->Render(model->endPos, 0.3f);
}
