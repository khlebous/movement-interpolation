#include "Engine.h"

Engine::Engine() :
	camera(std::make_shared<Camera>(glm::vec3(1.0f, 0.5f, 5.0f), -90.0f, 0.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f))),
	shader(std::make_shared<Shader>("PointerShader.vs", "PointerShader.fs")),
	axes(std::make_shared<Axes>()), gui(std::make_shared<Gui>())
{
	auto cameraGui = std::make_shared<CameraGui>();
	cameraGui->SetCamera(camera);
	gui->SetCameraGui(cameraGui);

	axes->SetShader(shader);
}

void Engine::Render(float deltaTime)
{
	UpdateCameraMatrices();
	UpdateShader();

	axes->Render();
}

void Engine::RenderGui()
{
	gui->Render();

}

void Engine::UpdateCameraMatrices()
{
	camera->UpdateProjectionMatrix();
	camera->UpdateViewMatrix();
}

void Engine::UpdateShader()
{
	shader->use();
	shader->setMat4(ShaderConstants::VIEW_MTX, camera->View);
	shader->setMat4(ShaderConstants::PROJECTION_MTX, camera->Projection);

	glUseProgram(0);
}
