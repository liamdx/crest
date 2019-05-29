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

	auto meshComponent = attachedEntity->GetComponent<MeshComponent>();
	if (meshComponent != nullptr)
	{
		if(meshComponent->meshIsConvex)
		{
			attachedEntity->transform->setScale(glm::vec3(1.0));
			shape = rib->addCollisionShape(createConvexMeshShape(meshComponent).get(), initPhysicsT, mass);
		}
		else
		{
			// duplicate code, remove me pls
			shape = rib->addCollisionShape(new rp3d::BoxShape(Vector3(3.0, 1.0, 3.0)), initPhysicsT, mass);
		}
		
	}
	else
	{
		shape = rib->addCollisionShape(new rp3d::BoxShape(Vector3(3.0, 1.0, 3.0)), initPhysicsT, mass);
	}
    
	

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


std::unique_ptr<CollisionShape> RigidbodyComponent::createConvexMeshShape(std::shared_ptr<MeshComponent> mesh)
{
	auto vertices = mesh->mesh.getVertexValues();
	auto indices = mesh->mesh.getIndexValues();

	unsigned int numFaces = mesh->mesh.faces.size();
	auto polygonFaces = new rp3d::PolygonVertexArray::PolygonFace[numFaces];
	rp3d::PolygonVertexArray::PolygonFace * face = polygonFaces;
	int lastStride = mesh->mesh.faces.at(0).numIndices;

	for (int f = 0; f < numFaces; f++) {
		// First vertex of the face in the indices array
		face->indexBase = f * lastStride;
		// Number of vertices in the face
		face->nbVertices = lastStride;
		lastStride = mesh->mesh.faces.at(f).numIndices;
		face++;
	}
	// Create the polygon vertex array
	auto polygonVertexArray = new rp3d::PolygonVertexArray(vertices.size() / 3,
		vertices.data(), 3 * sizeof(float),
		indices.data(), sizeof(unsigned int), numFaces, polygonFaces,
		rp3d::PolygonVertexArray::VertexDataType::VERTEX_FLOAT_TYPE,
		rp3d::PolygonVertexArray::IndexDataType::INDEX_INTEGER_TYPE)
		;
		
	PolyhedronMesh* phMesh = new rp3d::PolyhedronMesh(polygonVertexArray);
	// Create the convex mesh collision shape
	return(std::unique_ptr<rp3d::ConvexMeshShape>(new rp3d::ConvexMeshShape(phMesh)));

	    /*
		// Description of the six faces of the convex mesh
		polygonFaces = new rp3d::PolygonVertexArray::PolygonFace[6];
		rp3d::PolygonVertexArray::PolygonFace * face = polygonFaces;
		for (int f = 0; f < 6; f++) {
			// First vertex of the face in the indices array
			face - > indexBase = f * 4;
			// Number of vertices in the face
			face - > nbVertices = 4;
			face++;
		}
		// Create the polygon vertex array
		polygonVertexArray = new rp3d::PolygonVertexArray(8,
			vertices, 3 x sizeof(float),
			indices, sizeof(int), 6, polygonFaces,
			rp3d::PolygonVertexArray::VertexDataType::VERTEX_FLOAT_TYPE,
			rp3d::PolygonVertexArray::IndexDataType::INDEX_INTEGER_TYPE)
			;
		// Create the polyhedron mesh
		polyhedronMesh = new rp3d::PolyhedronMesh(polygonVertexArray
		);
		// Create the convex mesh collision shape
		convexMeshShape = new rp3d::ConvexMeshShape(polyhedronMesh);

*/
}


//polygonVertexArray = new rp3d::PolygonVertexArray(8,
//	vertices, 3 x sizeof(float),
//	indices, sizeof(int), 6, polygonFaces,
//	rp3d::PolygonVertexArray::VertexDataType::VERTEX_FLOAT_TYPE,
//	rp3d::PolygonVertexArray::IndexDataType::INDEX_INTEGER_TYPE)
//	;