#pragma once
#include "Common.h"
#include "Entity.h"
#include "components/MeshComponent.h"

class PhysicsManager
{
public:
	PhysicsManager();
	~PhysicsManager() {};
	

	// should we render the collision meshes?
	bool debugRender;


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
	//RigidBody* addRigidbody();
	//rp3d::CollisionBody* addCollisionBody();
	void addPhysicsEntity(std::shared_ptr<Entity> e) { physicsEntities.emplace_back(e); }
	void updateCollisionMeshes();


	// member vars
	std::vector<Mesh> debugMeshes;
	std::vector<std::shared_ptr<Entity>> physicsEntities;
	float accumulator, deltaTime, lastFrame, factor, fixedTimeStep;
	//rp3d::Vector3 gravity;
	//std::shared_ptr<rp3d::DynamicsWorld> world;
	Shader debugShader;

	glm::mat4 view, projection;

};
