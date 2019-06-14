#include "components/RigidbodyComponent.h"
#include "components/MeshComponent.h"

void RigidbodyComponent::init()
{
	mass = 4.0f;
	mass = 4.0f;
	physicsManager = attachedEntity->physicsManager;
	transform = attachedEntity->transform;
	attachedEntity->transform->update(0.0);
	attachedEntity->transform->setPhysicsOverride(true);

	shape = std::shared_ptr<btCollisionShape>(new btCapsuleShape(3.0, 2.0));


	btScalar mass(1.f);

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	bool isDynamic = (mass != 0.f);

	btVector3 localInertia(0, 0, 0);
	if (isDynamic)
		shape->calculateLocalInertia(mass, localInertia);

	btTransform initialTransform;
	btVector3 initialPosition(attachedEntity->transform->position.x, attachedEntity->transform->position.y, attachedEntity->transform->position.z);
	initialTransform.setOrigin(initialPosition);
	initialTransform.setRotation(btQuaternion::getIdentity());

	myMotionState = std::shared_ptr<btDefaultMotionState>(new btDefaultMotionState(initialTransform));
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState.get(), shape.get(), localInertia);
	rib = std::shared_ptr<btRigidBody>(new btRigidBody(rbInfo));

	
	//rib->translate(btVector3(transform->position.x, transform->position.y, transform->position.z));
	rib->setWorldTransform(initialTransform);
	myMotionState->setWorldTransform(initialTransform);
	physicsManager->addRigidbody(rib, shape);
	physicsManager->addPhysicsEntity(attachedEntity);
}

void RigidbodyComponent::applyCentralForce(glm::vec3 force)
{
	rib->applyCentralForce(btVector3(force.x, force.y, force.z));
}


void RigidbodyComponent::start()
{

}

void RigidbodyComponent::earlyUpdate(float deltaTime)
{
	if (rib && rib->getMotionState())
	{
		rib->getMotionState()->getWorldTransform(trans);
	}
	else
	{
		std::cout << "No Motion State " << std::endl;
	}

	// bleh this is nasty
	auto interpolatedPosition = trans.getOrigin();
	auto ir = trans.getRotation();
	glm::vec3 newPosition = glm::vec3(interpolatedPosition.getX(), interpolatedPosition.getY(), interpolatedPosition.getZ());
	glm::quat newQuatRotation;
	newQuatRotation.w = ir.getW();
	newQuatRotation.x = ir.getX();
	newQuatRotation.y = ir.getY();
	newQuatRotation.z = ir.getZ();
	glm::vec3 newRotation = glm::eulerAngles(newQuatRotation);
	if(newRotation.y == 0.0f)
	{
		newRotation.y = 0.01f;
	}

	transform->setPositionAbsolute(newPosition);
	transform->setEulerAnglesAbsolute(newRotation);
}

void RigidbodyComponent::update(float deltaTime)
{

	
}

void RigidbodyComponent::fixedUpdate()
{
	
}


void RigidbodyComponent::render(float deltaTime, glm::mat4 view)
{
	
}

void RigidbodyComponent::ui(float deltaTime)
{
	
}

void RigidbodyComponent::changeCollisionShape(btCollisionShape* newShape)
{
	rib->setCollisionShape(newShape);
}


void RigidbodyComponent::createConvexMeshShape()
{

}
