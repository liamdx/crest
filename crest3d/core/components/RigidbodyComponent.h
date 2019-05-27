#pragma once

#include "EngineComponent.h"
#include "Entity.h"
class RigidbodyComponent : public EngineComponent
{
public:
	RigidbodyComponent(std::shared_ptr<Entity> e) { attachedEntity = e; name = "RigidbodyComponent"; };
	~RigidbodyComponent() override {};

	void init() override;
	void start() override;
	void earlyUpdate(float deltaTime) override;
	void update(float deltaTime) override;
	void fixedUpdate() override;
	void render(float deltaTime) override;
	void ui(float deltaTime) override;

	std::shared_ptr<rp3d::RigidBody> rib;
	std::shared_ptr<PhysicsManager> physicsManager;
	std::shared_ptr<TransformComponent> transform;

	void changeCollisionShape(CollisionShape* newShape);


	//shape functionality pls
	inline float getMass() { return mass; }
	inline void setMass(float newMass) { mass = newMass; }
private:
	// react physics stuff
	rp3d::Transform currentPhysicsTransform;
	rp3d::Transform lastPhysicsTransform;
	rp3d::Transform interpolatedTransform;
	std::shared_ptr<rp3d::ProxyShape> shape;
	glm::vec3 position, eulerAngles;

	float mass;
};