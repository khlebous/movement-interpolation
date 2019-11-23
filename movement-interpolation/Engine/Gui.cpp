#include "Gui.h"

void Gui::Render()
{
	ImGui::Begin("Inspector", showInspector);

	if (ImGui::BeginTabBar("InspectoeTabBar", ImGuiTabBarFlags_None))
	{
		if (ImGui::BeginTabItem("Animation"))
		{
			animationGui->Render();

			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Camera"))
		{
			cameraGui->Render();

			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}

	ImGui::End();
}
