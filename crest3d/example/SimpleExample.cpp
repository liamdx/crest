#include "SimpleExample.h"

SimpleExample::SimpleExample(GLFWwindow* _window) : input(_window), window(_window)
{
	cubemapShader = new Shader("res/shaders/cubemap.vert", "res/shaders/cubemap.frag");
	model = new Model("res/models/cyborg/cyborg.obj");
	skybox = new Cubemap(faces);
	debugEntity = std::shared_ptr<Entity>(new Entity("John"));
	debugEntity->AddComponent(new ShaderComponent(debugEntity));
	debugEntity->AddComponent(new MeshComponent(debugEntity, Mesh(model->meshes[0])));
	cameraEntity = std::shared_ptr<Entity>(new Entity("Camera"));
	cameraEntity->AddComponent(new CameraComponent(cameraEntity));
	// projection = glm::perspectiveFov(glm::radians(75.0), (double)1280, (double)720, 0.1, 500.0);

}

void SimpleExample::initBehaviour()
{
	debugShader = debugEntity->GetComponent<ShaderComponent>();
	debugCamera = cameraEntity->GetComponent<CameraComponent>();
	debugShader->setProjection(debugCamera->GetProjectionMatrix());
	debugTransform = std::shared_ptr<TransformComponent>(debugEntity->transform);
    camTransform = std::shared_ptr<TransformComponent>(cameraEntity->transform);
	debugEntity->initBehaviour();
	cameraEntity->initBehaviour();
}


void SimpleExample::startBehaviour()
{
	debugEntity->startBehaviour();
	cameraEntity->startBehaviour();
} 

void SimpleExample::earlyUpdateBehaviour(float deltaTime)
{
	debugShader->setView(debugCamera->GetViewMatrix());
	debugEntity->earlyUpdateBehaviour();
}

void SimpleExample::updateBehaviour(float deltaTime)
{
	rotateCounter += deltaTime;
	if(rotateCounter >= 5.0f)
	{
		debugTransform->setEulerAngles(debugTransform->getEulerAngles() + glm::vec3(0, 90.0f, 0));
		rotateCounter = 0.0f;
	}

	debugTransform->setPosition(debugTransform->getPosition() + (debugTransform->getForward() * 1.0f) * deltaTime);
	//cameraEntity->transform->setPosition(debugTransform->getPosition() + glm::vec3(0, 3, -7));

	camTransform->setEulerAngles(camTransform->getEulerAngles() + glm::vec3(0, 90.0, 0));

	cubemapShader->use();
	cubemapShader->setMat4("projection", projection);
	cubemapShader->setMat4("view", debugCamera->GetViewMatrix());
	cubemapShader->setInt("cubemap", 0);
	skybox->Draw(*cubemapShader, debugCamera->GetViewMatrix(), debugCamera->GetProjectionMatrix());

	debugEntity->updateBehaviour();
}

void SimpleExample::uiBehaviour(float deltaTime)
{
	debugEntity->uiBehaviour();
}
