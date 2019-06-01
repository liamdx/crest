#include "components/CollisionBodyComponent.h"


void CollisionBodyComponent::init()
{
	physicsManager = attachedEntity->physicsManager;
	transform = attachedEntity->transform;

	col = std::shared_ptr<rp3d::CollisionBody>(physicsManager->addCollisionBody());
	currentPhysicsTransform = col->getTransform();
	lastPhysicsTransform = currentPhysicsTransform;
	interpolatedTransform = rp3d::Transform::identity();

	glm::vec3 initScale = transform->getScale();
	// rib->addCollisionShape(new rp3d::BoxShape(rp3d::Vector3(initScale.x, initScale.y, initScale.z)));

	//rigidbodies start at transform;
	rp3d::Transform initPhysicsT = rp3d::Transform::identity();
	initPhysicsT.setPosition(rp3d::Vector3(transform->position.x, transform->position.y, transform->position.z));
	glm::quat finalOrientation = glm::quat(transform->eulerAngles);
	initPhysicsT.setOrientation(rp3d::Quaternion(finalOrientation.x, finalOrientation.y, finalOrientation.z, finalOrientation.w));

	auto meshComponent = attachedEntity->GetComponent<MeshComponent>();

	if(meshComponent != nullptr)
	{
		shape = col->addCollisionShape(createMeshShape(), initPhysicsT);
	}
	else
	{
		shape = col->addCollisionShape(new rp3d::BoxShape(Vector3(attachedEntity->transform->scale.x, attachedEntity->transform->scale.y, attachedEntity->transform->scale.z)), initPhysicsT);
	}
	
	// shape = col->addCollisionShape(new rp3d::BoxShape(Vector3(attachedEntity->transform->scale.x, attachedEntity->transform->scale.y, attachedEntity->transform->scale.z)), initPhysicsT);
}

void CollisionBodyComponent::start()
{
	currentPhysicsTransform = col->getTransform();
	interpolatedTransform = Transform::interpolateTransforms(lastPhysicsTransform, currentPhysicsTransform, physicsManager->getFactor());
	lastPhysicsTransform = currentPhysicsTransform;

	auto interpolatedPosition = interpolatedTransform.getPosition();
	auto interpolatedRotation = interpolatedTransform.getOrientation();

	glm::vec3 finalPosition = glm::vec3(interpolatedPosition.x, interpolatedPosition.y, interpolatedPosition.z);
	glm::quat finalOrientation = glm::quat(interpolatedRotation.w, interpolatedRotation.x, interpolatedRotation.y, interpolatedRotation.z);
	glm::vec3 finalEulerAngles = glm::eulerAngles(finalOrientation);

	attachedEntity->transform->setPosition(finalPosition);
	attachedEntity->transform->setEulerAngles(finalEulerAngles);
	col->setIsSleeping(true);
}

void CollisionBodyComponent::earlyUpdate(float deltaTime)
{

}

void CollisionBodyComponent::update(float deltaTime)
{

}

void CollisionBodyComponent::fixedUpdate()
{

}


void CollisionBodyComponent::render(float deltaTime, glm::mat4 view)
{

}

void CollisionBodyComponent::ui(float deltaTime)
{

}


void CollisionBodyComponent::changeCollisionShape(CollisionShape* newShape)
{
	col->removeCollisionShape(shape);
	shape = col->addCollisionShape(newShape, rp3d::Transform::identity());
}


CollisionShape* CollisionBodyComponent::createMeshShape()
{
	auto meshComponent = attachedEntity->GetComponent<MeshComponent>();
	auto transform = attachedEntity->transform;
	collisionMeshVerts = meshComponent->mesh.getVertexValues();
	collisionMeshIndices = meshComponent->mesh.getIndexValues();

	triangleArray =
		new rp3d::TriangleVertexArray(collisionMeshVerts.size() / 3, &collisionMeshVerts[0], 3 * sizeof(float), collisionMeshIndices.size() / 3,
			&collisionMeshIndices[0], 3 * sizeof(int),
			rp3d::TriangleVertexArray::VertexDataType::VERTEX_FLOAT_TYPE,
			rp3d::TriangleVertexArray::IndexDataType::INDEX_INTEGER_TYPE);

	triangleMesh = new rp3d::TriangleMesh();
	// Add the triangle vertex array to the triangle mesh 
	triangleMesh->addSubpart(triangleArray);

	concaveMeshShape = new rp3d::ConcaveMeshShape(triangleMesh, Vector3(transform->scale.x, transform->scale.y, transform->scale.z));
	// Create the concave mesh shape 
	return(concaveMeshShape);
}
