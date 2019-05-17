#pragma once

#include "components/EngineComponent.h"
#include "Common.h"
class TransformComponent : public EngineComponent
{
	// basic
	glm::vec3 position;
	glm::vec3 eulerAngles;
	glm::vec3 scale;


	// direction vectors
	glm::vec3 forward;
	glm::vec3 right;
	glm::vec3 up;

	TransformComponent* parent = nullptr;

	TransformComponent() { name = "TransformComponent"; };
	~TransformComponent() {};

	void start() override;
	void earlyUpdate() override;
	void update() override;
	void ui() override;
};