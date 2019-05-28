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
	void addPosition(glm::vec3 newPosition);
	void setEulerAngles(glm::vec3 newRotation);
	void addEulerAngles(glm::vec3 newRotation);
	void setScale(glm::vec3 newScale);
	void addScale(glm::vec3 newScale);

	void updateModelMatrix();

	inline glm::vec3 getPosition() { return position; };
	inline glm::vec3 getEulerAngles() { return eulerAngles; };
	inline glm::vec3 getScale() { return scale; };

	inline glm::vec3 getLocalPosition() { return localPosition; };
	inline glm::vec3 getLocalEulerAngles() { return localEulerAngles; };
	inline glm::vec3 getLocalScale() { return localScale; };

	inline glm::vec3 getForward() { return forward; }
	inline glm::vec3 getRight() { return right; }
	inline glm::vec3 getUp() { return up; }

	void update(float deltaTime) override;

	std::shared_ptr<TransformComponent> parent = nullptr;
	std::shared_ptr<Entity> attachedEntity = nullptr;

	inline void setParent(std::shared_ptr<TransformComponent> newParent) { parent = newParent; }
	inline std::shared_ptr<TransformComponent> getParent() { return std::shared_ptr<TransformComponent>(parent); }

	inline void setOwnedEntity(std::shared_ptr<Entity> newEntity) { attachedEntity = newEntity; }
	inline std::shared_ptr<Entity> getOwnedEntity() { return std::shared_ptr<Entity>(attachedEntity); }

	inline glm::mat4 getModelMatrix() { return model; }

	TransformComponent();
	TransformComponent(std::shared_ptr<TransformComponent> _parent);
	~TransformComponent() {};

private:
	glm::mat4 model;
	void updateDirectionVectors();
	void clampRotation(float& value);
	void clampEulerAngles(glm::vec3& v);
};