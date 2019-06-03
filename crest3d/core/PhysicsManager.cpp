#include "PhysicsManager.h"
PhysicsManager::PhysicsManager() : debugShader("res/shaders/unassigned.vert", "res/shaders/unassigned.frag")
{
	lastFrame = 0.0;
	deltaTime = 0.0;
	accumulator = 0.0;
	fixedTimeStep = 1.0f / 60.0f;
	debugRender = true;
	//world = std::shared_ptr<DynamicsWorld>(new DynamicsWorld(gravity));
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
		//world->update(fixedTimeStep);

		// Decrease the accumulated time 
		accumulator -= fixedTimeStep;
	}

	factor = accumulator / fixedTimeStep;
}


void PhysicsManager::render(float deltaTime)
{
	if(debugRender)
	{
		debugShader.use();
		debugShader.setMat4("view", view);
		debugShader.setMat4("projection", projection);

		for (int i = 0; i < debugMeshes.size(); i++)
		{
			glm::mat4 model = physicsEntities.at(i)->transform->getModelMatrix();
			debugShader.setMat4("model", model);
			debugMeshes.at(i).Draw(debugShader);
		}

	}
	
}


//RigidBody* PhysicsManager::addRigidbody()
//{	
//	return(world->createRigidBody(rp3d::Transform::identity()));
//}
//
//
//
//rp3d::CollisionBody* PhysicsManager::addCollisionBody()
//{
//	return(world->createCollisionBody(rp3d::Transform::identity()));
//}

void PhysicsManager::updateCollisionMeshes()
{
	debugMeshes.clear();
	for(int i =0; i < physicsEntities.size(); i++)
	{
		auto e = physicsEntities.at(i);
		auto meshComponent = e->GetComponent<MeshComponent>();

		if(meshComponent != nullptr)
		{
			debugMeshes.emplace_back(Mesh(meshComponent->mesh.hullVertexPositions, meshComponent->mesh.hullIndices));
		}

	}
}
