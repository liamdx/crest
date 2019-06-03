#include "components/RigidbodyComponent.h"
#include "components/MeshComponent.h"

void RigidbodyComponent::init()
{
	mass = 4.0f;
	mass = 4.0f;
	physicsManager = attachedEntity->physicsManager;
	physicsManager->addPhysicsEntity(attachedEntity);
	transform = attachedEntity->transform;

	//rib = std::shared_ptr<RigidBody>(physicsManager->addRigidbody());
	//currentPhysicsTransform = rib->getTransform();
	//lastPhysicsTransform = currentPhysicsTransform;
	//interpolatedTransform = rp3d::Transform::identity();
	//
	//glm::vec3 initScale = transform->getScale();

	////rigidbodies start at transform;
	//rp3d::Transform initPhysicsT = rp3d::Transform::identity();
	//initPhysicsT.setPosition(rp3d::Vector3(transform->position.x, transform->position.y, transform->position.z));
	//glm::quat finalOrientation = glm::quat(transform->eulerAngles);
	//initPhysicsT.setOrientation(rp3d::Quaternion(finalOrientation.x, finalOrientation.y, finalOrientation.z, finalOrientation.w));
	//shape = rib->addCollisionShape(new rp3d::BoxShape(Vector3(4.0, 1.0, 4.0)), initPhysicsT, mass);
}

void RigidbodyComponent::start()
{

}

void RigidbodyComponent::earlyUpdate(float deltaTime)
{
	/*currentPhysicsTransform = rib->getTransform();
	interpolatedTransform = Transform::interpolateTransforms(lastPhysicsTransform, currentPhysicsTransform, physicsManager->getFactor());
	lastPhysicsTransform = currentPhysicsTransform;

	auto interpolatedPosition = interpolatedTransform.getPosition();
	auto interpolatedRotation = interpolatedTransform.getOrientation();

	glm::vec3 finalPosition = glm::vec3(interpolatedPosition.x, interpolatedPosition.y, interpolatedPosition.z);
	glm::quat finalOrientation = glm::quat(interpolatedRotation.w, interpolatedRotation.x, interpolatedRotation.y, interpolatedRotation.z);
	glm::vec3 finalEulerAngles = glm::eulerAngles(finalOrientation);

	attachedEntity->transform->setPosition(finalPosition);
	attachedEntity->transform->setEulerAngles(finalEulerAngles);*/
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

//
//void RigidbodyComponent::changeCollisionShape(CollisionShape* newShape)
//{
//	rib->removeCollisionShape(shape);
//	shape = rib->addCollisionShape(newShape, rp3d::Transform::identity(), mass);
//}
//
void RigidbodyComponent::createConvexMeshShape()
{
//	auto meshComponent = attachedEntity->GetComponent<MeshComponent>();
//
//	if(meshComponent != nullptr)
//	{
//		int numFaces = meshComponent->mesh.hullIndices.size() / 3;
//		int numVerts = meshComponent->mesh.hullVertexPositions.size() / 3;
//
//		polygonFaces = new rp3d::PolygonVertexArray::PolygonFace[numFaces];
//
//		face = polygonFaces;
//		for (int f = 0; f < numFaces; f++) {
//
//			// First vertex of the face in the indices array 
//			face->indexBase = f * 3;
//
//			// Number of vertices in the face 
//			face->nbVertices = 3;
//	
//			face++;
//		}
//
//		polygonVertexArray = new rp3d::PolygonVertexArray(numVerts, 
//			&(meshComponent->mesh.hullVertexPositions[0]), 3 * sizeof(float),
//			&(meshComponent->mesh.hullIndices[0]), sizeof(unsigned int), numFaces, polygonFaces,
//			rp3d::PolygonVertexArray::VertexDataType::VERTEX_FLOAT_TYPE,
//			rp3d::PolygonVertexArray::IndexDataType::INDEX_INTEGER_TYPE);
//
//		polyhedronMesh = new rp3d::PolyhedronMesh(polygonVertexArray);
//
//		rp3d::Vector3 scalingVec = rp3d::Vector3(4.0, 1.0, 4.0);
//		changeCollisionShape(new rp3d::ConvexMeshShape(polyhedronMesh, scalingVec));
//	}
}
