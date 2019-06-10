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
	
}


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
