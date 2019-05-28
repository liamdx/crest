#include "components/RigidbodyComponent.h"

void RigidbodyComponent::init()
{
	mass = 4.0f;
	position = glm::vec3(0.0);
	eulerAngles = glm::vec3(0.0);
	physicsManager = attachedEntity->physicsManager;
	transform = attachedEntity->transform;

	rib = std::shared_ptr<rp3d::RigidBody>(physicsManager->addRigidbody());
	currentPhysicsTransform = rib->getTransform();
	lastPhysicsTransform = currentPhysicsTransform;
	interpolatedTransform = rp3d::Transform::identity();
	
	glm::vec3 initScale = transform->getScale();
	// rib->addCollisionShape(new rp3d::BoxShape(rp3d::Vector3(initScale.x, initScale.y, initScale.z)));

	//rigidbodies start at transform;
	rp3d::Transform initPhysicsT = rp3d::Transform::identity();
	initPhysicsT.setPosition(rp3d::Vector3(transform->position.x, transform->position.y, transform->position.z));
	glm::quat finalOrientation = glm::quat(transform->eulerAngles);
	initPhysicsT.setOrientation(rp3d::Quaternion(finalOrientation.x, finalOrientation.y, finalOrientation.z, finalOrientation.w));

    shape = rib->addCollisionShape(new rp3d::BoxShape(Vector3(3.0, 1.0, 3.0)), initPhysicsT, mass);
	

}

void RigidbodyComponent::start()
{

}

void RigidbodyComponent::earlyUpdate(float deltaTime)
{
	currentPhysicsTransform = rib->getTransform();
	interpolatedTransform = Transform::interpolateTransforms(lastPhysicsTransform, currentPhysicsTransform, physicsManager->getFactor());
	lastPhysicsTransform = currentPhysicsTransform;

	auto interpolatedPosition = interpolatedTransform.getPosition();
	auto interpolatedRotation = interpolatedTransform.getOrientation();

	glm::vec3 finalPosition = glm::vec3(interpolatedPosition.x, interpolatedPosition.y, interpolatedPosition.z);
	glm::quat finalOrientation = glm::quat(interpolatedRotation.w, interpolatedRotation.x, interpolatedRotation.y, interpolatedRotation.z);
	glm::vec3 finalEulerAngles = glm::eulerAngles(finalOrientation);

	attachedEntity->transform->setPosition(finalPosition);
	attachedEntity->transform->setEulerAngles(finalEulerAngles);
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


void RigidbodyComponent::changeCollisionShape(CollisionShape* newShape)
{
	rib->removeCollisionShape(shape);
	shape = rib->addCollisionShape(newShape, rp3d::Transform::identity(), mass);
}
