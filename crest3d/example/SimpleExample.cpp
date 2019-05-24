#include "SimpleExample.h"

SimpleExample::SimpleExample(GLFWwindow* _window) : input(_window), window(_window)
{
	cubemapShader = new Shader("res/shaders/cubemap.vert", "res/shaders/cubemap.frag");
	model = new Model("res/models/cyborg/cyborg.obj");
	skybox = new Cubemap(faces);
	debugEntity = std::shared_ptr<Entity>(new Entity("John"));
	debugEntity->AddComponent(new ShaderComponent(debugEntity));
	debugEntity->AddComponent(new MeshComponent(debugEntity, Mesh(model->meshes[0])));
	projection = glm::perspectiveFov(glm::radians(75.0), (double)1280, (double)720, 0.1, 500.0);

}

void SimpleExample::initBehaviour()
{
	debugEntity->initBehaviour();
	debugShader = debugEntity->GetComponent<ShaderComponent>();
	debugShader->setProjection(projection);
	debugTransform = std::shared_ptr<TransformComponent>(debugEntity->transform);

}


void SimpleExample::startBehaviour()
{
	debugEntity->initBehaviour();
} 

void SimpleExample::earlyUpdateBehaviour(float deltaTime)
{
	debugShader->setView(cam.GetViewMatrix());
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

	cam.ProcessMouseMovement(input.xpos, -input.ypos, deltaTime);

	if (input.GetKeyW())
	{
		cam.ProcessKeyboard(FORWARD, deltaTime);

	}

	if (input.GetKeyS())
	{
		cam.ProcessKeyboard(BACKWARD, deltaTime);
	}

	if (input.GetKeyA())
	{
		cam.ProcessKeyboard(LEFT, deltaTime);
	}

	if (input.GetKeyD())
	{
		cam.ProcessKeyboard(RIGHT, deltaTime);
	}

	if (input.GetRightClick())
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		cam.canMove = true;
		input.GetMouseMovement();
		cam.ProcessMouseMovement(input.xpos, -input.ypos, deltaTime);
	}
	else
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	cubemapShader->use();
	cubemapShader->setMat4("projection", projection);
	cubemapShader->setMat4("view", cam.GetViewMatrix());
	cubemapShader->setInt("cubemap", 0);
	skybox->Draw(*cubemapShader, cam.GetViewMatrix(), projection);

	debugEntity->updateBehaviour();
}

void SimpleExample::uiBehaviour(float deltaTime)
{
	debugEntity->uiBehaviour();
}
