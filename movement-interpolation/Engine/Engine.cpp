#include "Engine.h"
#include "Configuration.h"
#include "Utils/QuaternionUtils.h"

Engine::Engine() :
	camera(std::make_shared<Camera>(glm::vec3(1.0f, 0.5f, 5.0f), -90.0f, 0.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f))),
	shader(std::make_shared<Shader>("PointerShader.vs", "PointerShader.fs")), 
	gui(std::make_shared<Gui>()),
	animation(std::make_shared<Animation>())
{
	auto axes = std::make_shared<Axes>();
	axes->SetShader(shader);

	std::shared_ptr<AnimationView> animationView = std::make_shared<AnimationView>();
	animationView->SetGameObject(axes);

	glm::vec3 startPos = glm::vec3(0);
	glm::vec3 startRot = glm::vec3(0);
	glm::vec3 endPos = glm::vec3(4, 1, 0);
	glm::vec3 endRot = glm::vec3(90, 45, 0);

	auto animationEulerModel = std::make_shared<AnimationModel<glm::vec3>>(
		Configuration<glm::vec3>(startPos, startRot),
		Configuration<glm::vec3>(endPos, endRot));
	animationView->SetAnimationEulerModel(animationEulerModel);

	auto animationQuatModel = std::make_shared<AnimationModel<glm::quat>>(
		Configuration<glm::quat>(startPos, QuaternionUtils::EulerDegreeToQuaternion(startRot)),
		Configuration<glm::quat>(endPos, QuaternionUtils::EulerDegreeToQuaternion(endRot)));
	animationView->SetAnimationQuatModel(animationQuatModel);

	animation->SetView(animationView);
	animation->SetEulerModel(animationEulerModel);
	animation->SetQuatModel(animationQuatModel);
	
	auto cameraGui = std::make_shared<CameraGui>();
	cameraGui->SetCamera(camera);
	
	auto animationGui = std::make_shared<AnimationGui>();
	animationGui->SetAnimation(animation);

	gui->SetCameraGui(cameraGui);
	gui->SetAnimationGui(animationGui);
}

void Engine::Update(float deltaTime)
{
	UpdateCameraMatrices();
	UpdateShader();

	animation->Update(deltaTime);
}

void Engine::Render(AnimationModelType type)
{
	animation->Render(type);
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
