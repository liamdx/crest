#include "components/CameraControllerComponent.h"
#include "Entity.h"

void CameraControllerComponent::earlyUpdate(float deltaTime)
{
	if (input->GetKeyW())
	{
		attachedEntity->transform->addPosition(attachedEntity->transform->getForward() * movementSpeed * deltaTime);
	}

	if (input->GetKeyS())
	{
		//BoneCam.ProcessKeyboard(BACKWARD, deltaTime);
		attachedEntity->transform->addPosition(-(attachedEntity->transform->getForward() * movementSpeed * deltaTime));
	}

	if (input->GetKeyA())
	{
		//BoneCam.ProcessKeyboard(LEFT, deltaTime);
		attachedEntity->transform->addPosition(-(attachedEntity->transform->getRight()) * movementSpeed * deltaTime);
	}

	if (input->GetKeyD())
	{
		//BoneCam.ProcessKeyboard(RIGHT, deltaTime);
		attachedEntity->transform->addPosition(attachedEntity->transform->getRight() * movementSpeed * deltaTime);
	}

	if (input->GetKeyE())
	{
		//BoneCam.ProcessKeyboard(RIGHT, deltaTime);
		attachedEntity->transform->addPosition(attachedEntity->transform->getUp() * movementSpeed * deltaTime);
	}

	if (input->GetKeyQ())
	{
		//BoneCam.ProcessKeyboard(RIGHT, deltaTime);
		attachedEntity->transform->addPosition(-(attachedEntity->transform->getUp()) * movementSpeed * deltaTime);
	}
	if(input->GetKeyLeftShift())
	{
		movementSpeed = initMoveSpeed * 3.0f;
	}
	else
	{
		movementSpeed = initMoveSpeed;
	}

	input->GetMouseMovement();
	float deltaX = input->xpos - lastX;
	float deltaY = -(input->ypos - lastY);
	lastX = input->xpos;
	lastY = input->ypos;

	// do mouseMovement
	deltaX = deltaX * 360.0f * mouseSensitivity * deltaTime;
	deltaY = deltaY * 360.0f *  mouseSensitivity * deltaTime;

	if (deltaX > 89.0f)
	{
		deltaX = 89.0f;
	}
	if (deltaX < -89.0f)
	{
		deltaX = -89.0f;
	}
	


	if (input->GetRightClick())
	{
		glfwSetInputMode(window.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		attachedEntity->transform->addEulerAngles(glm::vec3(deltaY, deltaX, 0));

	}
	else
	{
		glfwSetInputMode(window.get(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

CameraControllerComponent::CameraControllerComponent(std::shared_ptr<Entity> e ,std::shared_ptr<InputManager> _input)
{
	attachedEntity = e;
	name = "CameraControllerComponent";
	input = _input;
	lastX = 0.0f;
	lastY = 0.0f;
	mouseSensitivity = 0.3f;
	movementSpeed = 5.0f;
	initMoveSpeed = movementSpeed;
}
