#pragma once
#include "EngineComponent.h"
#include "RigidbodyComponent.h"

class CollisionShapeComponent : public EngineComponent
{
public:

	CollisionShapeComponent();
	~CollisionShapeComponent() override {};

	std::shared_ptr<btCollisionShape> getShape() { return shape; }

	// basic stuff
	void setShapeScale(glm::vec3 newScale);

	void createSphereShape();
	void createCapsuleShape();
	void createCubeShape();
	void createConvexHullShape();

	// this one may take a bit longer;
	void createMeshShape();



private:
	std::shared_ptr<btCollisionShape> shape;
	glm::vec3 scale;

};
