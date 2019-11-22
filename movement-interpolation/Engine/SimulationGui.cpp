#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "SimulationGui.h"
#include "..//ImGui/imgui_internal.h"

SimulationGui::SimulationGui()
{
	animationPercentage = 0.0f;
	intermediateFramesCount = 0;
}

void SimulationGui::Render()
{
	std::shared_ptr<SimulationModel<glm::vec3>> model = simulation->GetModel();

	bool disabledPushed = false;
	bool configurationChanged = false;
	
	if (simulation->isRunning)
	{
		PushDisabled();
		disabledPushed = true;

		animationPercentage = simulation->currentTime / simulation->animationTime;
	}

	if (ImGui::DragFloat("animation time", &simulation->animationTime, 0.1f))
	{
		if (simulation->animationTime < 0)
			simulation->animationTime = 0;
	}

	if (ImGui::DragInt("intermediate framescount", &intermediateFramesCount, 1))
	{
		if (intermediateFramesCount < 0)
			intermediateFramesCount = 0;

		configurationChanged = true;
	}

	if (ImGui::SliderFloat("##AnimationPercentage", &animationPercentage, 0, 1.0f))
		configurationChanged = true;

	if (ImGui::DragFloat3("start pos", &model->start.position[0], 0.1f))
		configurationChanged = true;

	if (ImGui::DragFloat3("start rotation", &model->start.rotation[0], 0.1f))
		configurationChanged = true;

	if (ImGui::DragFloat3("end pos", &model->end.position[0], 0.1f))
		configurationChanged = true;

	if (ImGui::DragFloat3("end rotation", &model->end.rotation[0], 0.1f))
		configurationChanged = true;

	if (ImGui::Button("Start animation"))
	{
		simulation->StartAnimation();
	}

	if (disabledPushed)
	{
		PopDisabled();
	}

	if (configurationChanged)
		simulation->RecalculateConfiguration(animationPercentage, intermediateFramesCount);
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
