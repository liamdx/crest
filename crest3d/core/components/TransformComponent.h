#pragma once

#include "components/EngineComponent.h"
#include "Common.h"
class Entity;

class TransformComponent : public EngineComponent
{
public:
	// basic
	glm::vec3 position;
	glm::vec3 eulerAngles;
	glm::vec3 scale;

	// local
	glm::vec3 localPosition;
	glm::vec3 localEulerAngles;
	glm::vec3 localScale;

	// direction vectors
	glm::vec3 forward;
	glm::vec3 right;
	glm::vec3 up;

	TransformComponent* parent = nullptr;

	Entity* attachedObject = nullptr;

	TransformComponent() { name = "TransformComponent"; };
	~TransformComponent() {};

	void start() override;
	void earlyUpdate() override;
	void update() override;
	void ui() override;
};