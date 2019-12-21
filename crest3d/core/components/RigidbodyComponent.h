#pragma once

#include "EngineComponent.h"
#include "Entity.h"
#include "PhysicsManager.h"

class RigidbodyComponent : public EngineComponent
{
public:
	RigidbodyComponent(std::shared_ptr<Entity> e) { attachedEntity = e; name = "RigidbodyComponent"; }

	// change pointers to unique_ptr
	~RigidbodyComponent() override;

	void init() override;
	void start() override;
	void earlyUpdate(float deltaTime) override;


	// Bullet stuff
	btRigidBody* rib;
	btCollisionShape* shape;
	btMotionState* myMotionState;

	void changeCollisionShape(std::shared_ptr<btCollisionShape> newShape);
	void applyCentralForce(glm::vec3 force);
	bool isKinematic;

	void SetCubeShape();
	void SetSphereShape();
	void SetCapsuleShape();
	

	//shape functionality pls
	inline float getMass() { return mass; }
	inline void setMass(float newMass) { mass = newMass; rib->setMassProps(newMass, btVector3(0, 0, 0)); }
	bool enabled;
	bool shouldLog = false;
	float mass;
	glm::vec3 centerOffset;
	void reset();
	glm::vec3 cubeDimensions, collisionScale;
	float capsuleRadius, capsuleHeight;
	float sphereRadius;

	glm::vec3 bulletToGlm(const btVector3& v) { return glm::vec3(v.getX(), v.getY(), v.getZ()); }

	btVector3 glmToBullet(const glm::vec3& v) { return btVector3(v.x, v.y, v.z); }

	glm::quat bulletToGlm(const btQuaternion& q) { return glm::quat(q.getW(), q.getX(), q.getY(), q.getZ()); }

	btQuaternion glmToBullet(const glm::quat& q) { return btQuaternion(q.x, q.y, q.z, q.w); }

	btMatrix3x3 glmToBullet(const glm::mat3& m) { return btMatrix3x3(m[0][0], m[1][0], m[2][0], m[0][1], m[1][1], m[2][1], m[0][2], m[1][2], m[2][2]); }

	// btTransform does not contain a full 4x4 matrix, so this transform is lossy.
	// Affine transformations are OK but perspective transformations are not.
	btTransform glmToBullet(const glm::mat4& m)
	{
		glm::mat3 m3(m);
		return btTransform(glmToBullet(m3), glmToBullet(glm::vec3(m[3][0], m[3][1], m[3][2])));
	}

	float radToDegree(float rad) { return rad * 57.2958; }
	float degreeToRad(float deg) { return deg / 57.2958; }
	glm::mat4 bulletToGlm(const btTransform& t)
	{
		glm::mat4 m(0.0);
		const btMatrix3x3& basis = t.getBasis();
		// rotation
		for (int r = 0; r < 3; r++)
		{
			for (int c = 0; c < 3; c++)
			{
				m[c][r] = basis[r][c];
			}
		}
		// traslation
		btVector3 origin = t.getOrigin();
		m[3][0] = origin.getX();
		m[3][1] = origin.getY();
		m[3][2] = origin.getZ();
		// unit scale
		m[0][3] = 0.0f;
		m[1][3] = 0.0f;
		m[2][3] = 0.0f;
		m[3][3] = 1.0f;
		return m;
	}
	
	
private:

	float previousFrameMass;
	btTransform trans;
};
