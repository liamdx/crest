#include "components/CameraControllerComponent.h"
#include "Entity.h"

#include "EngineManager.h"

void CameraControllerComponent::earlyUpdate(float deltaTime)
{
	if (input->GetKeyW())
	{
		attachedEntity->transform->position += (attachedEntity->transform->forward * movementSpeed * deltaTime);
	}

	if (input->GetKeyS())
	{
		//BoneCam.ProcessKeyboard(BACKWARD, deltaTime);
		attachedEntity->transform->position += (-(attachedEntity->transform->forward) * movementSpeed * deltaTime);
	}

	if (input->GetKeyA())
	{
		//BoneCam.ProcessKeyboard(LEFT, deltaTime);
		attachedEntity->transform->position += (-(attachedEntity->transform->right) * movementSpeed * deltaTime);
	}

	if (input->GetKeyD())
	{
		//BoneCam.ProcessKeyboard(RIGHT, deltaTime);
		attachedEntity->transform->position += (attachedEntity->transform->right * movementSpeed * deltaTime);
	}

	if (input->GetKeyE())
	{
		//BoneCam.ProcessKeyboard(RIGHT, deltaTime);
		attachedEntity->transform->position += (attachedEntity->transform->up * movementSpeed * deltaTime);
	}

	if (input->GetKeyQ())
	{
		//BoneCam.ProcessKeyboard(RIGHT, deltaTime);
		attachedEntity->transform->position += (-(attachedEntity->transform->up) * movementSpeed * deltaTime);
	}
	if (input->GetKeyLeftShift())
	{
		movementSpeed = initMoveSpeed * 6.0f;
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
	deltaY = deltaY * 360.0f * mouseSensitivity * deltaTime;

	if (input->GetRightClick())
	{
		SDL_ShowCursor(0);
		attachedEntity->transform->eulerAngles += glm::vec3(deltaY, deltaX, 0);
	}
	else
	{
		SDL_ShowCursor(1);
	}
}

CameraControllerComponent::CameraControllerComponent(std::shared_ptr<Entity> e, std::shared_ptr<InputManager> _input)
{
	attachedEntity = e;
	name = "CameraControllerComponent";
	input = _input;
	lastX = 0.0f;
	lastY = 0.0f;
	mouseSensitivity = 0.1f;
	movementSpeed = 5.0f;
	initMoveSpeed = movementSpeed;
}