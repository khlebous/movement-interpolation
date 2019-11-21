#include "SimulationView.h"

void SimulationView::Render()
{
	gameObject->Render(model->startPos);
	gameObject->Render(model->endPos);
}
