#pragma once
#include "EngineComponent.h"
#include "RigidbodyComponent.h"

class CollisionShapeComponent : public EngineComponent
{
public:

	CollisionShapeComponent(std::shared_ptr<Entity> e) { attachedEntity = e; createSphereShape(); }
	~CollisionShapeComponent() override {};

	std::shared_ptr<btCollisionShape> getShape() { return shape; }

	// basic stuff
	void setShapeScale(glm::vec3 newScale);

	void createSphereShape();
	void createCapsuleShape();
	void createCubeShape();
	void createConvexHullShape(std::shared_ptr<MeshComponent> meshComponent);

	void updateRigidbodyShape();

	// this one may take a bit longer;
	void createMeshShape();

private:

	// hmm, maybe references?
	std::shared_ptr<btCollisionShape> shape;
	glm::vec3 scale;

	// convex hull stuff
	std::unique_ptr<btShapeHull> shapeHull;
	std::unique_ptr<btConvexHullShape> convexHullShape;
	std::vector<btVector3> getConvexHullMeshPoints(std::shared_ptr<Mesh> mesh);
};
