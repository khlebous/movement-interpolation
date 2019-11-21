#include "SimulationGui.h"

void SimulationGui::Render()
{
	ImGui::DragFloat3("start pos", &model->startPos[0], 0.1f);
	ImGui::DragFloat3("end pos", &model->endPos[0], 0.1f);
}
