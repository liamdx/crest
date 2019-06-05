#include "PhysicsManager.h"
PhysicsManager::PhysicsManager() : debugShader("res/shaders/unassigned.vert", "res/shaders/unassigned.frag")
{
	lastFrame = 0.0;
	deltaTime = 0.0;
	accumulator = 0.0;
	fixedTimeStep = 1.0f / 60.0f;
	debugRender = true;

	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	overlappingPairCache = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver();
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0.0, -10.0, 0.0));
	debugRenderer = new DebugRenderer();
	debugRenderer->setDebugMode(btIDebugDraw::DebugDrawModes::DBG_DrawWireframe);
	dynamicsWorld->setDebugDrawer(debugRenderer);
	projection = glm::mat4(1.0);
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
		dynamicsWorld->stepSimulation(fixedTimeStep, 10);

		// Decrease the accumulated time 
		accumulator -= fixedTimeStep;
	}

	factor = accumulator / fixedTimeStep;
}


void PhysicsManager::render(float deltaTime)
{
	debugRenderer->COLORS.clear();
	debugRenderer->LINES.clear();
	dynamicsWorld->debugDrawWorld();
	debugRenderer->bindBuffers();
	debugShader.use();
	debugShader.setMat4("view", view);
	debugShader.setMat4("projection", projection);
	debugRenderer->doDraw();
}



void PhysicsManager::addRigidbody(std::shared_ptr<btRigidBody> rib, std::shared_ptr<btCollisionShape> col)
{

	collisionShapes.push_back(col.get());
	dynamicsWorld->addRigidBody(rib.get());
}


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
