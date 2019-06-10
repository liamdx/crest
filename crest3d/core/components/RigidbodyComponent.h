#pragma once

#include "EngineComponent.h"
#include "Entity.h"
#include "PhysicsManager.h"

class RigidbodyComponent : public EngineComponent
{
public:
	RigidbodyComponent(std::shared_ptr<Entity> e) { attachedEntity = e; name = "RigidbodyComponent"; };

	// change pointers to unique_ptr
	~RigidbodyComponent() override {  };

	void init() override;
	void start() override;
	void earlyUpdate(float deltaTime) override;
	void update(float deltaTime) override;
	void fixedUpdate() override;
	void render(float deltaTime, glm::mat4 view) override;
	void ui(float deltaTime) override;

	// Bullet stuff
	std::shared_ptr<btRigidBody> rib;
	std::shared_ptr<btCollisionShape> shape;
	std::shared_ptr<btDefaultMotionState> myMotionState;
	std::shared_ptr<PhysicsManager> physicsManager;
	std::shared_ptr<TransformComponent> transform;

	void changeCollisionShape(btCollisionShape* newShape);
	void createConvexMeshShape();

	//shape functionality pls
	inline float getMass() { return mass; }
	inline void setMass(float newMass) { mass = newMass; rib->setMassProps(newMass, btVector3(0, 0, 0)); }


private:
	btTransform trans;
	float mass;
};
