#include "PhysicsManager.h"

PhysicsManager::PhysicsManager() : gravity(0.0, -9.81, 0.0), world(gravity)
{
	lastFrame = 0.0;
	deltaTime = 0.0;
	accumulator = 0.0;
}

void PhysicsManager::update(float deltaTime)
{
	accumulator += deltaTime;

	if(accumulator > 1.0f)
	{
		accumulator = 0.0f;
	}
	while (accumulator >= fixedTimeStep) {

		// Update the Dynamics world with a constant time step 
		world.update(fixedTimeStep);

		std::cout << "bleh" << std::endl;

		// Decrease the accumulated time 
		accumulator -= fixedTimeStep;
	}

	factor = accumulator / fixedTimeStep;
}

rp3d::RigidBody* PhysicsManager::addRigidbody()
{
	return(world.createRigidBody(rp3d::Transform::identity()));
}
