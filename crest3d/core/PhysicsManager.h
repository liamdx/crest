#pragma once
#include "Common.h"

class PhysicsManager
{
public:
	PhysicsManager();
	~PhysicsManager() {};
	static constexpr float fixedTimeStep = 1.0f / 60.0f;
	rp3d::Vector3 gravity;

	void setGravity(glm::vec3 _gravity);
	void update(float deltaTime);

	rp3d::RigidBody* addRigidbody();

	inline float getFactor() { return factor; }

private:
	float accumulator, deltaTime, lastFrame, factor;
	std::unique_ptr<rp3d::DynamicsWorld> world;
};