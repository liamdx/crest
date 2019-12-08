#pragma once

#include "EngineComponent.h"
#include "Entity.h"
#include "PhysicsManager.h"

class RigidbodyComponent : public EngineComponent
{
public:
	RigidbodyComponent(std::shared_ptr<Entity> e) { attachedEntity = e; name = "RigidbodyComponent"; }

	// change pointers to unique_ptr
	~RigidbodyComponent() override;

	void init() override;
	void start() override;
	void earlyUpdate(float deltaTime) override;


	// Bullet stuff
	btRigidBody* rib;
	btCollisionShape* shape;
	btMotionState* myMotionState;

	void changeCollisionShape(std::shared_ptr<btCollisionShape> newShape);
	void applyCentralForce(glm::vec3 force);

	void SetCubeShape(glm::vec3 dimensions);
	void SetSphereShape(glm::vec3 dimensions);
	void SetCapsuleShape(glm::vec3 dimensions);
	

	//shape functionality pls
	inline float getMass() { return mass; }
	inline void setMass(float newMass) { mass = newMass; rib->setMassProps(newMass, btVector3(0, 0, 0)); }
	bool enabled;
	bool shouldLog = false;
	float mass;
	glm::vec3 centerOffset;
	void reset();
	
private:

	float previousFrameMass;
	btTransform trans;
};
