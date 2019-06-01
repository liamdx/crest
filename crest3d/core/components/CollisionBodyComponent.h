#include "EngineComponent.h"
#include "Entity.h"
#include "MeshComponent.h"


class CollisionBodyComponent : public EngineComponent
{
public:
	CollisionBodyComponent(std::shared_ptr<Entity> e) { attachedEntity = e; name = "CollisionBodyComponent"; };
	~CollisionBodyComponent() override {};

	void init() override;
	void start() override;
	void earlyUpdate(float deltaTime) override;
	void update(float deltaTime) override;
	void fixedUpdate() override;
	void render(float deltaTime, glm::mat4 view) override;
	void ui(float deltaTime) override;

	std::shared_ptr<rp3d::CollisionBody> col;
	std::shared_ptr<PhysicsManager> physicsManager;
	std::shared_ptr<TransformComponent> transform;

	void changeCollisionShape(CollisionShape* newShape);
	CollisionShape* createMeshShape();


	std::vector<float> collisionMeshVerts;
	std::vector<int> collisionMeshIndices;

	// react physics stuff
	rp3d::Transform currentPhysicsTransform;
	rp3d::Transform lastPhysicsTransform;
	rp3d::Transform interpolatedTransform;
	rp3d::ProxyShape* shape;

	rp3d::TriangleVertexArray* triangleArray;
	rp3d::ConcaveMeshShape* concaveMeshShape;
	rp3d::TriangleMesh* triangleMesh;

private:


};