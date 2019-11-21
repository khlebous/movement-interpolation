#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "SimulationGui.h"
#include "..//ImGui/imgui_internal.h"

SimulationGui::SimulationGui()
{
	animationPercentage = 0.0f;
}

void SimulationGui::Render()
{
	std::shared_ptr<SimulationModel> model = simulation->GetModel();

	bool disabledPushed = false;
	if (model->isRunning)
	{
		PushDisabled();
		disabledPushed = true;

		animationPercentage = model->currentTime / model->animationTime;
		animationPercentage = model->currentTime / model->animationTime;
	}

	if (ImGui::DragFloat("animation time", &model->animationTime, 0.1f))
	{
		if (model->animationTime < 0)
			model->animationTime = 0;
	}

	if (ImGui::Button("Start animation"))
	{
		simulation->StartAnimation();
	}

	if (ImGui::SliderFloat("##AnimationPercentage", &animationPercentage, 0, 1.0f))
	{
		simulation->SetCurrentPosition(animationPercentage);
	}

	if (ImGui::DragFloat3("start pos", &model->startPos[0], 0.1f))
	{
		simulation->SetCurrentPosition(animationPercentage);
	}

	if (ImGui::DragFloat3("end pos", &model->endPos[0], 0.1f))
	{
		simulation->SetCurrentPosition(animationPercentage);
	}

	if (disabledPushed)
	{
		PopDisabled();
	}
}

void SimulationGui::PushDisabled()
{
	ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
	ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
}

void SimulationGui::PopDisabled()
{
	ImGui::PopItemFlag();
	ImGui::PopStyleVar();
}
