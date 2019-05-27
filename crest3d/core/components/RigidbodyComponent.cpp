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
	const std::unique_ptr<rp3d::BoxShape> initshape(new rp3d::BoxShape(Vector3(initScale.x, initScale.y, initScale.z)));
	
    shape = std::shared_ptr<rp3d::ProxyShape>(rib->addCollisionShape(initshape.get(), rp3d::Transform::identity(), mass));
	

}

void RigidbodyComponent::start()
{

}

void RigidbodyComponent::earlyUpdate(float deltaTime)
{
	currentPhysicsTransform = rib->getTransform();
	interpolatedTransform = Transform::interpolateTransforms(lastPhysicsTransform, currentPhysicsTransform, physicsManager->getFactor());
	lastPhysicsTransform = currentPhysicsTransform;
}

void RigidbodyComponent::update(float deltaTime)
{
	
}

void RigidbodyComponent::fixedUpdate()
{
	
}


void RigidbodyComponent::render(float deltaTime)
{
	
}

void RigidbodyComponent::ui(float deltaTime)
{
	
}


void RigidbodyComponent::changeCollisionShape(CollisionShape* newShape)
{
	rib->removeCollisionShape(shape.get());
	shape = std::shared_ptr<rp3d::ProxyShape>(rib->addCollisionShape(newShape, rp3d::Transform::identity(), mass));
}