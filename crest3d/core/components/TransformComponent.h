#pragma once

#include "components/EngineComponent.h"
#include "Common.h"

// forward declaration of entity class
class Entity;

class TransformComponent : public EngineComponent
{
public:
	// FINAL transform
	glm::vec3 position, eulerAngles, scale;
	// local transform
	glm::vec3 localPosition, localEulerAngles, localScale;
	// direction vectors
	glm::vec3 forward, right, up;
	//world directions
	glm::vec3 worldForward, worldRight, worldUp;

	// member funcs
	void setPosition(glm::vec3 newPosition);
	void setEulerAngles(glm::vec3 newRotation);
	void setScale(glm::vec3 newScale);

	glm::vec3 getPosition() { return position; };
	glm::vec3 getEulerAngles() { return eulerAngles; };
	glm::vec3 getScale() { return scale; };

	glm::vec3 getLocalPosition() { return localPosition; };
	glm::vec3 getLocalEulerAngles() { return localEulerAngles; };
	glm::vec3 getLocalScale() { return localScale; };

	TransformComponent* parent = nullptr;
	Entity* attachedEntity = nullptr;

	inline void setParent(TransformComponent* newParent) { parent = newParent; }
	inline TransformComponent* getParent() { return parent; }

	inline void setOwnedEntity(Entity* newEntity) { attachedEntity = newEntity; }
	inline Entity* getOwnedEntity() { return attachedEntity; }

	TransformComponent();
	TransformComponent(TransformComponent* _parent);
	~TransformComponent() {};

	// use camera class to work out how to work out direction vectors.

private:
	void updateDirectionVectors();
};