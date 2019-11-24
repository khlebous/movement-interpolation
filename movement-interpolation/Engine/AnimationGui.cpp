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
	std::shared_ptr<AnimationModel<glm::vec3>> eModel = animation->GetEulerModel();
	std::shared_ptr<AnimationModel<glm::quat>> qModel = animation->GetQuaternionModel();

	bool disabledPushed = false;
	
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

		animation->SetIntermediateFrames(intermediateFramesCount);
	}

	if (ImGui::SliderFloat("##animation_percentage", &animationPercentage, 0, 1.0f))
		animation->SetAnimationPercentage(animationPercentage);

	if (ImGui::DragFloat3("start pos", &eModel->start.position[0], 0.1f))
		animation->OnEulerStartPositionChanged();
	
	if (ImGui::DragFloat3("end pos", &eModel->end.position[0], 0.1f))
		animation->OnEulerEndPositionChanged();
	
	ImGui::Spacing();

	if (ImGui::DragFloat3("start rotation", &eModel->start.rotation[0], 0.1f))
		animation->OnEulerStartRotationChanged();

	if (ImGui::DragFloat3("end rotation", &eModel->end.rotation[0], 0.1f))
		animation->OnEulerEndRotationChanged();

	ImGui::Spacing();

	if (ImGui::DragFloat4("start rot q", &qModel->start.rotation[0], 0.01f))
		animation->OnQuaternionStartRotationChanged();

	if (ImGui::DragFloat4("end rot q", &qModel->end.rotation[0], 0.01f))
		animation->OnQuaternionEndRotationChanged();


	if (ImGui::Button("Start animation"))
		animation->StartAnimation();

	if (disabledPushed)
	{
		PopDisabled();
	}
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
