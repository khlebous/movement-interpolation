#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "AnimationGui.h"
#include "..//ImGui/imgui_internal.h"

AnimationGui::AnimationGui()
{
	animationPercentage = 0.0f;
	intermediateFramesCount = 0;
}

void AnimationGui::Render()
{
	std::shared_ptr<AnimationModel<glm::vec3>> model = animation->GetModel();

	bool disabledPushed = false;
	bool configurationChanged = false;
	
	if (animation->isRunning)
	{
		PushDisabled();
		disabledPushed = true;

		animationPercentage = animation->currentTime / animation->animationTime;
	}

	if (ImGui::DragFloat("animation time", &animation->animationTime, 0.1f))
	{
		if (animation->animationTime < 0)
			animation->animationTime = 0;
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
		animation->StartAnimation();
	}

	if (disabledPushed)
	{
		PopDisabled();
	}

	if (configurationChanged)
		animation->RecalculateConfiguration(animationPercentage, intermediateFramesCount);
}

void AnimationGui::PushDisabled()
{
	ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
	ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
}

void AnimationGui::PopDisabled()
{
	ImGui::PopItemFlag();
	ImGui::PopStyleVar();
}
