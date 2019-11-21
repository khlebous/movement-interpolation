#include "CameraGui.h"

void CameraGui::Render()
{
	if (ImGui::DragFloat3("position", &camera->Position[0], 0.01f))
		camera->UpdateCameraVectors();
	if (ImGui::DragFloat("yaw", &camera->Yaw))
		camera->UpdateCameraVectors();
	if (ImGui::SliderFloat("pitch", &camera->Pitch, -89, 89))
		camera->UpdateCameraVectors();
}
