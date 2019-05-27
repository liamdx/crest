#include "PhysicsManager.h"

PhysicsManager::PhysicsManager() : gravity(0.0, -9.81, 0.0)
{
	world = std::unique_ptr<rp3d::DynamicsWorld>(new rp3d::DynamicsWorld(gravity));
	lastFrame = 0.0;
	deltaTime = 0.0;
	accumulator = 0.0;
}

void PhysicsManager::update(float deltaTime)
{
	accumulator += deltaTime;

	while (accumulator >= fixedTimeStep) {

		// Update the Dynamics world with a constant time step 
		world->update(fixedTimeStep);

		// Decrease the accumulated time 
		accumulator -= fixedTimeStep;
	}

	factor = accumulator / fixedTimeStep;
}

rp3d::RigidBody* PhysicsManager::addRigidbody()
{
	return(world->createRigidBody(rp3d::Transform::identity()));
}