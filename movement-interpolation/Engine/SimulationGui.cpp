#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "SimulationGui.h"

void SimulationGui::Render()
{
	std::shared_ptr<SimulationModel> model = simulation->GetModel();

	if (ImGui::DragFloat("animation time", &model->animationTime, 0.1f))
	{
		if (model->animationTime < 0)
			model->animationTime = 0;
	}

	if (ImGui::Button("Start animation"))
	{
		simulation->StartAnimation();
	}

	sprintf(progressBuf, "%0.2f/%0.2f", model->currentTime, model->animationTime);
	ImGui::ProgressBar(model->currentTime / model->animationTime, ImVec2(0.f, 0.f), progressBuf);

	ImGui::DragFloat3("start pos", &model->startPos[0], 0.1f);
	ImGui::DragFloat3("end pos", &model->endPos[0], 0.1f);
}
