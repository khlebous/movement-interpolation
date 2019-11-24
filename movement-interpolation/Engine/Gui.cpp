#include "Gui.h"

void Gui::Render()
{
	ImGui::BeginMainMenuBar();
	
	if (ImGui::BeginMenu("Animation"))
	{
		animationGui->RenderMenu();
		ImGui::EndMenu();
	}

	ImGui::Text(" | ");

	if (ImGui::BeginMenu("Camera"))
	{
		cameraGui->Render();
		ImGui::EndMenu();
	}
	
	ImGui::Text(" | ");

	ImGuiIO& io = ImGui::GetIO();
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

	ImGui::EndMainMenuBar();

	animationGui->Render();
}
