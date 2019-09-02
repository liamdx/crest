#pragma once
#include "Common.h"
#include "Entity.h"
#include "components/MeshComponent.h"
#include "DebugRenderer.h"

class PhysicsManager
{
public:
	PhysicsManager();
	~PhysicsManager() {};
	

	// should we render the collision meshes?
	bool debugRender;
	DebugRenderer* debugRenderer;


	// what we do each frame
	void update(float deltaTime);
	void render(float deltaTime);

	// getter setters
	inline float getFactor() { return factor; }
	inline void setView(glm::mat4 newView) { view = newView; }
	inline glm::mat4 getView() { return view; }
	inline void setProjection(glm::mat4 newProjection) { projection = newProjection; }
	inline glm::mat4 getProjection() { return projection; }

	// pm functions
	void addRigidbody(std::shared_ptr<btRigidBody> rib, std::shared_ptr<btCollisionShape> col);
	void addPhysicsEntity(std::shared_ptr<Entity> e) { physicsEntities.emplace_back(e); }

	Shader debugShader;
	// member vars
	std::vector<std::shared_ptr<Entity>> physicsEntities;
	float accumulator, deltaTime, lastFrame, factor, fixedTimeStep;
	//bullet variables
	btVector3 gravity;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btBroadphaseInterface* overlappingPairCache;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;
	btAlignedObjectArray<btCollisionShape*> collisionShapes;

	glm::mat4 view, projection;

};
