#include "components/CollisionShapeComponent.h"

void CollisionShapeComponent::createSphereShape()
{
	shape = std::shared_ptr<btCollisionShape>(new btSphereShape(1));
}

void CollisionShapeComponent::createCapsuleShape()
{
	shape = std::shared_ptr<btCollisionShape>(new btCapsuleShape(1, 2));
}

void CollisionShapeComponent::createCubeShape()
{
	shape = std::shared_ptr<btCollisionShape>(new btBoxShape(btVector3(1, 1, 1)));
}

void CollisionShapeComponent::createConvexHullShape(std::shared_ptr<MeshComponent> meshComponent)
{
	auto points = getConvexHullMeshPoints(meshComponent->mesh);
	auto mesh = meshComponent->mesh;
	btConvexHullShape* _convexHullShape = new btConvexHullShape();
	for (unsigned int i = 0; i < mesh->vertices.size(); i++)
	{
		btVector3 point = btVector3(mesh->vertices.at(i).position.x, mesh->vertices.at(i).position.y, mesh->vertices.at(i).position.z);
		_convexHullShape->addPoint(point, false);
	}

	_convexHullShape->recalcLocalAabb();
	shapeHull = std::unique_ptr<btShapeHull>(new btShapeHull(_convexHullShape));
	shapeHull->buildHull(0, 1);    // note: parameter is ignored by buildHull
	convexHullShape = std::unique_ptr<btConvexHullShape>(new btConvexHullShape(
		(const btScalar*)shapeHull->getVertexPointer(), shapeHull->numVertices(), sizeof(btVector3)));
	shape = std::shared_ptr<btCollisionShape>(convexHullShape.get());
	delete _convexHullShape;
}

void CollisionShapeComponent::updateRigidbodyShape()
{
	auto scale = attachedEntity->transform->scale;
	shape->setLocalScaling(btVector3(scale.x, scale.y, scale.z));
}

// private smaller funcs

std::vector<btVector3> CollisionShapeComponent::getConvexHullMeshPoints(std::shared_ptr<Mesh> mesh)
{
	std::vector<btVector3> points;

	for (unsigned int i = 0; i < mesh->vertices.size(); i++)
	{
		btVector3 point = btVector3(mesh->vertices.at(i).position.x, mesh->vertices.at(i).position.x, mesh->vertices.at(i).position.x);
	}

	return points;
}