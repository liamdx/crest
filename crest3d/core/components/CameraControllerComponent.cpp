#include "components/CameraControllerComponent.h"
#include "Entity.h"

#include "EngineManager.h"
#include "serialization/Serializer.hpp"

void CameraControllerComponent::earlyUpdate(float deltaTime)
{
	if (!useContoller) {
		if (useMovement) {
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
				movementSpeed = sprintSpeed;
			}
			else
			{
				movementSpeed = initMoveSpeed;
			}
		}
		float deltaX = input->xpos - lastX;
		float deltaY = -(input->ypos - lastY);
		lastX = input->xpos;
		lastY = input->ypos;

		// do mouseMovement
		deltaX = deltaX * 360.0f * mouseSensitivity * deltaTime;
		deltaY = deltaY * 360.0f * mouseSensitivity * deltaTime;
		

		if (input->GetRightClick())
		{
			glfwSetInputMode(attachedEntity->engineManager->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			// SDL_ShowCursor(0);
			attachedEntity->transform->eulerAngles = attachedEntity->transform->eulerAngles + glm::vec3(deltaY, deltaX, 0);
			activeLastFrame = true;
		}
		else
		{
			if (activeLastFrame)
			{
				glfwSetInputMode(attachedEntity->engineManager->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				activeLastFrame = true;
			}
		}
		
	}

	if(useContoller)
	{
		if (useMovement) {
			float xMovement = input->controller1.left_x_input;
			float yMovement = input->controller1.left_y_input;


			bool isSprinting = input->controller1.left_bumper;

			glm::vec3 x_movement = attachedEntity->transform->right * xMovement;
			glm::vec3 y_movement = attachedEntity->transform->forward * yMovement;


			if (isSprinting)
			{
				movementSpeed = 10.0f;
			}
			else
			{
				movementSpeed = 5.0f;
			}
			attachedEntity->transform->position += ((x_movement + y_movement) * movementSpeed * deltaTime);
		}
		float xLook = input->controller1.right_x_input;
		float yLook = input->controller1.right_y_input;
		attachedEntity->transform->eulerAngles += (glm::vec3(yLook, xLook, 0.0f) * 360.0f * deltaTime);

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
	movementSpeed = 10.0f;
	initMoveSpeed = movementSpeed;
	sprintSpeed = initMoveSpeed * 3.0f;
	useContoller = false;
	useMovement = true;
}

tinyxml2::XMLElement* CameraControllerComponent::serialize_component(tinyxml2::XMLDocument* doc)
{
	auto ccElement = doc->NewElement("CameraControllerComponent");
	// ..
	ccElement->LinkEndChild(Serializer::SerializeFloat(mouseSensitivity, "mouseSensitivity", doc));
	ccElement->LinkEndChild(Serializer::SerializeFloat(movementSpeed, "movementSpeed", doc));
	ccElement->LinkEndChild(Serializer::SerializeFloat(sprintSpeed, "sprintSpeed", doc));
	ccElement->LinkEndChild(Serializer::SerializeBool(useContoller, "useController", doc));
	ccElement->LinkEndChild(Serializer::SerializeBool(useMovement, "useMovement", doc));
	return ccElement;
}
