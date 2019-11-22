#include "Engine.h"
#include "Configuration.h"

Engine::Engine() :
	camera(std::make_shared<Camera>(glm::vec3(1.0f, 0.5f, 5.0f), -90.0f, 0.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f))),
	shader(std::make_shared<Shader>("PointerShader.vs", "PointerShader.fs")), 
	gui(std::make_shared<Gui>()),
	simulation(std::make_shared<Simulation>())
{
	auto axes = std::make_shared<Axes>();
	axes->SetShader(shader);

	std::shared_ptr<SimulationView> simulationView = std::make_shared<SimulationView>();
	simulationView->SetGameObject(axes);

	auto simulationEulerModel = std::make_shared<SimulationModel<glm::vec3>>(
		Configuration<glm::vec3>(glm::vec3(0), glm::vec3(0)),
		Configuration<glm::vec3>(glm::vec3(4, 1, 0), glm::vec3(20, 30 ,40)));
	simulationView->SetSimulationEulerModel(simulationEulerModel);

	simulation->SetView(simulationView);
	simulation->SetEulerModel(simulationEulerModel);
	
	auto cameraGui = std::make_shared<CameraGui>();
	cameraGui->SetCamera(camera);
	
	auto simulationGui = std::make_shared<SimulationGui>();
	simulationGui->SetSimulation(simulation);

	gui->SetCameraGui(cameraGui);
	gui->SetSimulationGui(simulationGui);
}

void Engine::Render(float deltaTime)
{
	UpdateCameraMatrices();
	UpdateShader();

	simulation->Update(deltaTime);
	simulation->Render();
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
