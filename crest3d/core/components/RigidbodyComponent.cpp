#include "components/RigidbodyComponent.h"
#include "components/MeshComponent.h"
#include "EngineManager.h"
#include "serialization/Serializer.hpp"

void RigidbodyComponent::init()
{
	if(attachedEntity != nullptr)
	{
		shouldLog = false;
		enabled = true;
		mass = 1.0f;
		attachedEntity->transform->update(0.0);
		attachedEntity->transform->setPhysicsOverride(false);
		rib = attachedEntity->engineManager->physicsManager->addRigidbody(attachedEntity);
		btVector3 initialPosition = btVector3(attachedEntity->transform->position.x, attachedEntity->transform->position.y, attachedEntity->transform->position.z);
		rib->translate(initialPosition);
		shape = rib->getCollisionShape();
		myMotionState = rib->getMotionState();
		centerOffset = glm::vec3(0.0f);
		sphereRadius = 1.0f;
		capsuleRadius = 1.0f;
		capsuleHeight = 1.0f;
		collisionScale = glm::vec3(1.0f);
		cubeDimensions = glm::vec3(1.0f);
		linearFactor = glm::vec3(1.0f);
		angularFactor = glm::vec3(1.0f);
	}
	
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

void RigidbodyComponent::SetCubeShape()
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
	btVector3 dim(cubeDimensions.x, cubeDimensions.y, cubeDimensions.z);
	rib->setCollisionShape(new btBoxShape(dim));
	btVector3 scale(collisionScale.x, collisionScale.y, collisionScale.z);
	rib->getCollisionShape()->setLocalScaling(scale);
	attachedEntity->engineManager->physicsManager->dynamicsWorld->addRigidBody(rib);
}

void RigidbodyComponent::SetCapsuleShape()
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
	rib->setCollisionShape(new btCapsuleShape(capsuleRadius, capsuleHeight));
	btVector3 scale(collisionScale.x, collisionScale.y, collisionScale.z);
	rib->getCollisionShape()->setLocalScaling(scale);
	attachedEntity->engineManager->physicsManager->dynamicsWorld->addRigidBody(rib);
}

void RigidbodyComponent::SetSphereShape()
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
	rib->setCollisionShape(new btSphereShape(sphereRadius));
	btVector3 scale(collisionScale.x, collisionScale.y, collisionScale.z);
	rib->getCollisionShape()->setLocalScaling(scale);
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
			rib->setLinearFactor(glmToBullet(linearFactor));
			rib->setAngularFactor(glmToBullet(angularFactor));
		}
		else
		{
			std::cout << "No Motion State " << std::endl;
		}

		glm::vec3 position = bulletToGlm(trans.getOrigin());
		glm::vec3 radEulerAngles = glm::eulerAngles(bulletToGlm(trans.getRotation()));
		glm::vec3 eulerAngles = glm::vec3(radToDegree(radEulerAngles.x), radToDegree(radEulerAngles.y), radToDegree(radEulerAngles.z));


		attachedEntity->transform->position = position;
		attachedEntity->transform->eulerAngles = eulerAngles;

		if(shouldLog)
		{
			std::stringstream s;
			s << "Position: " << glm::to_string(position) << " Euler: " << glm::to_string(eulerAngles) << std::endl;
			Debug::Message<RigidbodyComponent>(s.str().c_str());
		}
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

tinyxml2::XMLElement* RigidbodyComponent::serialize_component(tinyxml2::XMLDocument* doc)
{
	auto rbcElement = doc->NewElement("RigidbodyComponent");

	rbcElement->LinkEndChild(Serializer::SerializeBool(isKinematic, "isKinematic",doc));
	rbcElement->LinkEndChild(Serializer::SerializeBool(enabled, "enabled", doc));
	rbcElement->LinkEndChild(Serializer::SerializeFloat(mass, "mass", doc));
	rbcElement->LinkEndChild(Serializer::SerializeFloat(capsuleRadius, "capsuleRadius", doc));
	rbcElement->LinkEndChild(Serializer::SerializeFloat(capsuleHeight, "capsuleHeight", doc));
	rbcElement->LinkEndChild(Serializer::SerializeFloat(sphereRadius, "sphereRadius", doc));
	rbcElement->LinkEndChild(Serializer::SerializeVec3(centerOffset, "centerOffset", doc));
	rbcElement->LinkEndChild(Serializer::SerializeVec3(linearFactor, "linearFactor", doc));
	rbcElement->LinkEndChild(Serializer::SerializeVec3(angularFactor, "angularFactor", doc));
	rbcElement->LinkEndChild(Serializer::SerializeVec3(cubeDimensions, "cubeDimensions", doc));
	rbcElement->LinkEndChild(Serializer::SerializeVec3(collisionScale, "collisionScale", doc));

	return rbcElement;
}

void RigidbodyComponent::deserialize_component(tinyxml2::XMLElement* e)
{
	
}
