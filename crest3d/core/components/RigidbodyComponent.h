#pragma once

#include "EngineComponent.h"
#include "Entity.h"
#include "PhysicsManager.h"

class RigidbodyComponent : public EngineComponent
{
public:
	RigidbodyComponent(std::shared_ptr<Entity> e) { attachedEntity = e; name = "RigidbodyComponent"; };

	// change pointers to unique_ptr
	~RigidbodyComponent() override {  };

	void init() override;
	void start() override;
	void earlyUpdate(float deltaTime) override;
	void update(float deltaTime) override;
	void fixedUpdate() override;
	void render(float deltaTime, glm::mat4 view) override;
	void ui(float deltaTime) override;

	//std::shared_ptr<rp3d::RigidBody> rib;
	std::shared_ptr<PhysicsManager> physicsManager;
	std::shared_ptr<TransformComponent> transform;

	//void changeCollisionShape(CollisionShape* newShape);
	void createConvexMeshShape();

	//shape functionality pls
	inline float getMass() { return mass; }
	inline void setMass(float newMass) { mass = newMass; }

	// react physics stuff
	/*rp3d::Transform currentPhysicsTransform;
	rp3d::Transform lastPhysicsTransform;
	rp3d::Transform interpolatedTransform;
	rp3d::ProxyShape* shape;*/


private:
	// convex hull shape stuff
	/*rp3d::PolygonVertexArray::PolygonFace* face;
	ConvexMeshShape* convexMeshShape;
	PolyhedronMesh* polyhedronMesh;
	PolygonVertexArray* polygonVertexArray;
	rp3d::PolygonVertexArray::PolygonFace *polygonFaces;*/

	float mass;
};
