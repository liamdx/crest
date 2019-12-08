#include "components/RigidbodyComponent.h"
#include "components/MeshComponent.h"
#include "EngineManager.h"

void RigidbodyComponent::init()
{
	enabled = true;
	mass = 1.0f;
	attachedEntity->transform->update(0.0);
	attachedEntity->transform->setPhysicsOverride(true);
	rib = attachedEntity->engineManager->physicsManager->addRigidbody(attachedEntity);
	shape = rib->getCollisionShape();
	myMotionState = rib->getMotionState();
	centerOffset = glm::vec3(0.0f);
}

RigidbodyComponent::~RigidbodyComponent()
{
	attachedEntity->engineManager->physicsManager->dynamicsWorld->removeRigidBody(rib);
	delete rib; delete shape; delete myMotionState;
};


void RigidbodyComponent::start()
{
	
}


void RigidbodyComponent::applyCentralForce(glm::vec3 force)
{
	rib->applyCentralForce(btVector3(force.x, force.y, force.z));
}

void RigidbodyComponent::SetCubeShape(glm::vec3 dimensions)
{
	attachedEntity->engineManager->physicsManager->dynamicsWorld->removeRigidBody(rib);
	btVector3 inertia(0, 0, 0);
	rib->getCollisionShape()->calculateLocalInertia(mass, inertia);
	rib->setActivationState(DISABLE_DEACTIVATION);
	rib->setMassProps(mass, inertia);
	rib->setLinearFactor(btVector3(1, 1, 1));
	rib->setAngularFactor(btVector3(1, 1, 1));
	rib->updateInertiaTensor();
	rib->clearForces();
	btTransform transform;
	transform.setIdentity();
	float x = attachedEntity->transform->position.x;
	float y = attachedEntity->transform->position.y;
	float z = attachedEntity->transform->position.z;
	transform.setOrigin(btVector3(x, y, z));
	btVector3 dim(dimensions.x, dimensions.y, dimensions.z);
	rib->setCollisionShape(new btBoxShape(dim));
	btVector3 scale(1, 1, 1);
	rib->getCollisionShape()->setLocalScaling(scale);
	rib->setWorldTransform(transform);
	attachedEntity->engineManager->physicsManager->dynamicsWorld->addRigidBody(rib);
}

btVector3 quatToEuler(btQuaternion quat)
{
	float  heading, attitude, bank;
	glm::quat q1;
	q1.x = quat.getX();
	q1.y = quat.getY();
	q1.z = quat.getZ();
	q1.w = quat.getW();
	double test = q1.x * q1.y + q1.z * q1.w;
	if (test > 0.499) { // singularity at north pole
		heading = 2 * atan2(q1.x, q1.w);
		attitude = M_PI / 2;
		bank = 0;
		return btVector3(0, 0, 0);
	}
	if (test < -0.499) { // singularity at south pole
		heading = -2 * atan2(q1.x, q1.w);
		attitude = -M_PI / 2;
		bank = 0;
		return  btVector3(0, 0, 0);
	}
	double sqx = q1.x * q1.x;
	double sqy = q1.y * q1.y;
	double sqz = q1.z * q1.z;
	heading = atan2(2 * q1.y * q1.w - 2 * q1.x * q1.z, 1 - 2 * sqy - 2 * sqz);
	attitude = asin(2 * test);
	bank = atan2(2 * q1.x * q1.w - 2 * q1.y * q1.z, 1 - 2 * sqx - 2 * sqz);
	btVector3 vec(bank, heading, attitude);
	return vec;
}


void RigidbodyComponent::earlyUpdate(float deltaTime)
{
	if (enabled)
	{
		if(previousFrameMass == 0.0f && mass != previousFrameMass)
		{
			reset();
		}
		if (rib && rib->getMotionState())
		{
			rib->updateInertiaTensor();
			myMotionState = rib->getMotionState();
			rib->setMassProps(mass, rib->getLocalInertia());
			rib->getMotionState()->getWorldTransform(trans);
		}
		else
		{
			std::cout << "No Motion State " << std::endl;
		}

		// bleh this is nasty
		trans.getOpenGLMatrix(glm::value_ptr(attachedEntity->transform->model));
		attachedEntity->transform->model = glm::scale(attachedEntity->transform->model,attachedEntity->transform->scale);
		
		//auto interpolatedPosition = trans.getOrigin();
		//auto ir = trans.getRotation();
		//glm::vec3 newPosition = glm::vec3(interpolatedPosition.getX(), interpolatedPosition.getY(), interpolatedPosition.getZ());
		//newPosition += centerOffset;
		//btVector3 newEuler = quatToEuler(trans.getRotation());
		//glm::vec3 finalEuler = glm::vec3(newEuler.getX() * 90, newEuler.getY(), newEuler.getZ());

		//attachedEntity->transform->position = newPosition;
		//attachedEntity->transform->eulerAngles = finalEuler;
	}

	previousFrameMass = mass;
}

void RigidbodyComponent::changeCollisionShape(std::shared_ptr<btCollisionShape> newShape)
{
	rib->setCollisionShape(newShape.get());
	shape = newShape.get();
}

void RigidbodyComponent::reset()
{
	attachedEntity->engineManager->physicsManager->dynamicsWorld->removeRigidBody(rib);
	btVector3 inertia(0, 0, 0);
	rib->getCollisionShape()->calculateLocalInertia(mass, inertia);
	rib->setActivationState(DISABLE_DEACTIVATION);
	rib->setMassProps(mass, inertia);
	rib->setLinearFactor(btVector3(1, 1, 1));
	rib->setAngularFactor(btVector3(1, 1, 1));
	rib->updateInertiaTensor();
	rib->clearForces();
	btTransform transform;
	transform.setIdentity();
	float x = attachedEntity->transform->position.x;
	float y = attachedEntity->transform->position.y;
	float z = attachedEntity->transform->position.z;
	transform.setOrigin(btVector3(x, y, z));
	rib->getCollisionShape()->setLocalScaling(btVector3(1, 1, 1));
	rib->setWorldTransform(transform);
	attachedEntity->engineManager->physicsManager->dynamicsWorld->addRigidBody(rib);

}
