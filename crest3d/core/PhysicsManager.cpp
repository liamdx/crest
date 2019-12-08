#include "PhysicsManager.h"
PhysicsManager::PhysicsManager() : debugShader("res/shaders/unassigned.vert", "res/shaders/unassigned.frag")
{
	lastFrame = 0.0;
	deltaTime = 0.0;
	accumulator = 0.0;
	fixedTimeStep = 1.0f / 60.0f;
	debugRender = false;

	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	overlappingPairCache = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver();
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0.0, -9.81f, 0.0));
	debugRenderer = new DebugRenderer();
	debugRenderer->setDebugMode(btIDebugDraw::DebugDrawModes::DBG_DrawWireframe);
	dynamicsWorld->setDebugDrawer(debugRenderer);
	projection = glm::mat4(1.0);
}
PhysicsManager::~PhysicsManager()
{
	delete collisionConfiguration;
	delete dispatcher;
	delete overlappingPairCache;
	delete solver;
	delete dynamicsWorld;
	delete debugRenderer;
}


void PhysicsManager::update(float deltaTime)
{
	accumulator += deltaTime;

	if (accumulator > 1.0f)
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
	if (debugRender)
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
}

btRigidBody* PhysicsManager::addRigidbody(std::shared_ptr<Entity> attachedEntity)
{
	btTransform initialTransform;
	btVector3 initialPosition(attachedEntity->transform->position.x, attachedEntity->transform->position.y, attachedEntity->transform->position.z);
	initialTransform.setOrigin(initialPosition);
	initialTransform.setRotation(btQuaternion::getIdentity());
	auto myMotionState = new btDefaultMotionState(initialTransform);
	auto shape = new btCapsuleShape(1.0, 1.0);
	btScalar mass(1.f);
	btVector3 localInertia(0, 0, 0);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, shape, localInertia);
	btRigidBody* newRib = new btRigidBody(rbInfo);
	return newRib;
}

btRigidBody* PhysicsManager::addRigidbody()
{
	btTransform initialTransform;
	btVector3 initialPosition(0,0,0);
	initialTransform.setOrigin(initialPosition);
	initialTransform.setRotation(btQuaternion::getIdentity());
	auto myMotionState = new btDefaultMotionState(initialTransform);
	auto shape = new btCapsuleShape(1.0, 1.0);
	btScalar mass(1.f);
	btVector3 localInertia(0, 0, 0);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, shape, localInertia);
	btRigidBody* newRib = new btRigidBody(rbInfo);
	dynamicsWorld->addRigidBody(newRib);
	return newRib;
}