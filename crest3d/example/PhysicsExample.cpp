#include "PhysicsExample.h"

PhysicsExample::PhysicsExample(GLFWwindow* _window)
{
	window = std::shared_ptr<GLFWwindow>(_window);
	pm = std::shared_ptr<PhysicsManager>(new PhysicsManager());
	scene = std::unique_ptr<Scene>(new Scene("debugScene",pm));
	input = std::shared_ptr<InputManager>(new InputManager(_window));

	cubemapShader = new Shader("res/shaders/cubemap.vert", "res/shaders/cubemap.frag");
	skybox = new Cubemap(faces);

	cameraRotation = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	cameraPosition = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	levelRotation = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	levelPosition = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
}


void PhysicsExample::initBehaviour()
{
	//temporarily initialise everything here

	Model m("res/models/cyborg/cyborg.obj");
	Model level("res/models/swamp/map_1.obj");

	levelEntity = scene->AddModelEntity(level);
	for (int i = 0; i < levelEntity->children.size(); i++)
	{
		//levelEntity->children.at(i)->AddComponent(new RigidbodyComponent(levelEntity->children.at(i)));
		//levelEntity->children.at(i)->GetComponent<RigidbodyComponent>()->rib->setType(BodyType::KINEMATIC);
	}

	cyborgEntity = scene->AddModelEntity(m);
	for(int i = 0; i < cyborgEntity->children.size(); i++)
	{
		//cyborgEntity->children.at(i)->AddComponent(new RigidbodyComponent(cyborgEntity->children.at(i)));
	}

	


	cameraEntity = scene->AddCameraEntity();
	cameraEntity->AddComponent(new CameraControllerComponent(cameraEntity, input));
	std::shared_ptr<CameraControllerComponent> camController = cameraEntity->GetComponent<CameraControllerComponent>();
	camController->window = window;

	cam = cameraEntity->GetComponent<CameraComponent>();
	
	cyborgEntity->transform->addPosition(glm::vec3(0, 1, 0));
	cameraEntity->transform->addPosition(glm::vec3(0, 4, 0));
	levelEntity->transform->addPosition(glm::vec3(0, -3, 0));

	scene->initBehaviour();
}

void PhysicsExample::startBehaviour()
{
	scene->startBehaviour();
}

void PhysicsExample::earlyUpdateBehaviour(float deltaTime)
{
	pm->update(deltaTime);
	scene->earlyUpdateBehaviour(deltaTime);
}

void PhysicsExample::fixedUpdateBehaviour()
{
	scene->fixedUpdateBehaviour();
}

void PhysicsExample::updateBehaviour(float deltaTime)
{
	scene->updateBehaviour(deltaTime);
	
	//cameraEntity->transform->setPosition(glm::vec3(cameraPosition.x, cameraPosition.y, cameraPosition.z));
	// cameraEntity->transform->setEulerAngles(glm::vec3(cameraRotation.x, cameraRotation.y, cameraRotation.z));
	levelEntity->transform->setPosition(glm::vec3(levelPosition.x, levelPosition.y, levelPosition.z));
	levelEntity->transform->setEulerAngles(glm::vec3(levelRotation.x, levelRotation.y, levelRotation.z));
	cyborgEntity->transform->setPosition(glm::vec3(cameraPosition.x, cameraPosition.y, cameraPosition.z));
	cyborgEntity->transform->setEulerAngles(glm::vec3(cameraRotation.x, cameraRotation.y, cameraRotation.z));

}

void PhysicsExample::renderBehaviour(float deltaTime)
{
	std::shared_ptr<CameraComponent> cam = cameraEntity->GetComponent<CameraComponent>();

	cubemapShader->use();
	cubemapShader->setMat4("projection", cam->GetProjectionMatrix());
	cubemapShader->setMat4("view", glm::mat4(glm::mat3(cam->GetViewMatrix())));
	cubemapShader->setInt("cubemap", 0);

	skybox->Draw(*cubemapShader);

	scene->renderBehaviour(deltaTime);
}

void PhysicsExample::uiBehaviour(float deltaTime)
{
	if (ImGui::Begin("Physics Example"))
	{
		ImGui::SliderFloat3("Level Position", &levelPosition.x, -100, 100);
		ImGui::SliderFloat3("Level Rotation", &levelRotation.x, -180, 180);
		ImGui::SliderFloat3("Cyborg Position", &cameraPosition.x, -100, 100);
		ImGui::SliderFloat3("Cyborg Rotation", &cameraRotation.x, -180, 180);

		ImGui::End();
	}
	scene->uiBehaviour(deltaTime);
}


