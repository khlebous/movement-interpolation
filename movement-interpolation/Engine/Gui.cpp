#include "Gui.h"

void Gui::Render()
{
	ImGui::Begin("Inspector", showInspector);
	cameraGui->Render();
	ImGui::End();
}
