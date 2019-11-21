#include "SimulationGui.h"

void SimulationGui::Render()
{
	if (ImGui::DragFloat("animation time", &model->animationTime, 0.1f))
	{
		if (model->animationTime < 0)
			model->animationTime = 0;
	}

	ImGui::DragFloat3("start pos", &model->startPos[0], 0.1f);
	ImGui::DragFloat3("end pos", &model->endPos[0], 0.1f);
}
