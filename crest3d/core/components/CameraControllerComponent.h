#pragma once

#include "EngineComponent.h"
#include "InputManager.h"

class CameraControllerComponent : public EngineComponent
{
public:
	CameraControllerComponent(std::shared_ptr<Entity>e, std::shared_ptr<InputManager> _input);
	~CameraControllerComponent() override {};

	void earlyUpdate(float deltaTime) override;

	// can be turned in to references
	std::shared_ptr<InputManager> input;
	GLFWwindow* window;

	float mouseSensitivity;
	float movementSpeed , sprintSpeed, initMoveSpeed;

	bool useContoller, useMovement, activeLastFrame;

	tinyxml2::XMLElement* serialize_component(tinyxml2::XMLDocument* doc) override;
	
private:
	float lastX, lastY;
};
