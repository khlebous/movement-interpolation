#include "AnimationGui.h"
#include "..//ImGui/imgui_internal.h"
#include "Constnants/WindowConstants.h"

AnimationGui::AnimationGui()
{
	animationPercentage = 0.0f;
	intermediateFramesCount = 0;
}

void AnimationGui::RenderMenu()
{
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

	
	ImGui::Spacing();

	if (ImGui::Button("Start animation"))
		animation->StartAnimation();

	if (disabledPushed)
	{
		PopDisabled();
	}
}

void AnimationGui::Render()
{
	RenderEulerWindow();
	RenderQuaternionWindow();
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

void AnimationGui::RenderEulerWindow()
{
	ImGui::Begin("Euler settings", showEuler, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
	ImGui::SetWindowSize(ImVec2(WindowConstants::UI_WIDTH, WindowConstants::UI_HEIGHT()));
	ImGui::SetWindowPos(ImVec2(WindowConstants::EULER_UI_X(), WindowConstants::EULER_UI_Y()));

	std::shared_ptr<AnimationModel<glm::vec3>> eModel = animation->GetEulerModel();

	if (ImGui::DragFloat3("start pos", &eModel->start.position[0], 0.1f))
		animation->OnEulerStartPositionChanged();

	if (ImGui::DragFloat3("end pos", &eModel->end.position[0], 0.1f))
		animation->OnEulerEndPositionChanged();

	ImGui::Spacing();

	if (ImGui::DragFloat3("start rotation", &eModel->start.rotation[0], 0.1f))
		animation->OnEulerStartRotationChanged();

	if (ImGui::DragFloat3("end rotation", &eModel->end.rotation[0], 0.1f))
		animation->OnEulerEndRotationChanged();

	ImGui::End();
}

void AnimationGui::RenderQuaternionWindow()
{
	ImGui::Begin("Quaternion settings", showEuler, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
	ImGui::SetWindowSize(ImVec2(WindowConstants::UI_WIDTH, WindowConstants::UI_HEIGHT()));
	ImGui::SetWindowPos(ImVec2(WindowConstants::QUATERNION_UI_X(), WindowConstants::QUATERNION_UI_Y()));

	std::shared_ptr<AnimationModel<glm::quat>> qModel = animation->GetQuaternionModel();

	if (ImGui::DragFloat4("start rot q", &qModel->start.rotation[0], 0.01f))
		animation->OnQuaternionStartRotationChanged();

	if (ImGui::DragFloat4("end rot q", &qModel->end.rotation[0], 0.01f))
		animation->OnQuaternionEndRotationChanged();

	ImGui::Spacing();

	if (ImGui::RadioButton("LERP", animation->qRotType == LERP))
	{
		animation->qRotType = LERP;
		animation->OnQuaternionInterpolationTypeChanged();
	}
	if (ImGui::RadioButton("SLERP", animation->qRotType == SLERP))
	{
		animation->qRotType = SLERP;
		animation->OnQuaternionInterpolationTypeChanged();
	}
	ImGui::End();
}
