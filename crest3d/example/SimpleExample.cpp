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
	sponza = new Model("res/models/swamp/map_1.obj");
	projection = glm::perspectiveFov(glm::radians(75.0), (double)1280, (double)720, 0.1, 500.0);
	zOffset = 0.0f;
	yOffset = 0.0f;
	cameraRotation = 0.0f;

}

void SimpleExample::initBehaviour()
{
	debugEntity->initBehaviour();
	cameraEntity->initBehaviour();
	debugShader = debugEntity->GetComponent<ShaderComponent>();
	debugCamera = cameraEntity->GetComponent<CameraComponent>();
    debugTransform = debugEntity->transform;
	debugTransform->setScale(glm::vec3(4.0f));
    camTransform = cameraEntity->transform;
	debugShader->setProjection(projection);
}


void SimpleExample::startBehaviour()
{
	debugEntity->startBehaviour();
	cameraEntity->startBehaviour();
} 

void SimpleExample::earlyUpdateBehaviour(float deltaTime)
{

	// debugShader->shader->use();
	// debugShader->shader->setMat4("model", sponzaModel);
	// sponza->Draw(*debugShader->shader);

	rotateCounter += deltaTime;
	if (rotateCounter >= 5.0f)
	{
		std::cout << "debugEntity position = " << glm::to_string(debugTransform->position) << std::endl;
		std::cout << "debugEntity rotation = " << glm::to_string(debugTransform->eulerAngles) << std::endl;
		std::cout << "debugEntity forward = " << glm::to_string(debugTransform->forward) << std::endl;

		std::cout << "cameraEntity position = " << glm::to_string(camTransform->position) << std::endl;
		std::cout << "cameraEntity rotation = " << glm::to_string(camTransform->eulerAngles) << std::endl;
		std::cout << "cameraEntity forward = " << glm::to_string(camTransform->forward) << std::endl;

		debugTransform->setEulerAngles(debugTransform->getEulerAngles() + glm::vec3(0, -90.0f, 0));
		rotateCounter = 0.0f;
	}

	glm::vec3 movement = debugTransform->getForward();
	movement.y = 0.0;
	debugTransform->addPosition(movement * deltaTime * 0.5f);


	camTransform->setPosition(glm::vec3(debugTransform->getPosition()) + ((glm::vec3(-debugTransform->forward)) * zOffset) + (glm::vec3(-debugTransform->up)) * yOffset);
    camTransform->setEulerAngles(glm::vec3(debugTransform->getEulerAngles() + glm::vec3(0, cameraRotation, 0)));
	debugEntity->earlyUpdateBehaviour(deltaTime);
	cameraEntity->earlyUpdateBehaviour(deltaTime);

}

void SimpleExample::updateBehaviour(float deltaTime)
{
	
	

	debugEntity->updateBehaviour(deltaTime);
	cameraEntity->updateBehaviour(deltaTime);
	
}

void SimpleExample::renderBehaviour(float deltaTime)
{

	debugShader->setView(debugCamera->GetViewMatrix());
	cubemapShader->use();
	cubemapShader->setMat4("projection", projection);
	cubemapShader->setMat4("view", glm::mat4(glm::mat3(debugCamera->GetViewMatrix())));
	cubemapShader->setInt("cubemap", 0);

	skybox->Draw(*cubemapShader);

	glm::mat4 sponzaModel = glm::mat4(1.0);
	sponzaModel = glm::translate(sponzaModel, glm::vec3(0, -15, 0));
	sponzaModel = glm::scale(sponzaModel, glm::vec3(3.0f));
	debugShader->shader->use();
	debugShader->shader->setMat4("model", sponzaModel);
	sponza->Draw(*debugShader->shader);

	cameraEntity->renderBehaviour(deltaTime);
	debugEntity->renderBehaviour(deltaTime);
}


void SimpleExample::uiBehaviour(float deltaTime)
{
	ImGui::SliderFloat("Radius", &zOffset, -100, 100);
	ImGui::SliderFloat("Height", &yOffset, -100, 100);
	ImGui::SliderFloat("Rotation", &cameraRotation, -180, 180);
	debugEntity->uiBehaviour(deltaTime);
}
