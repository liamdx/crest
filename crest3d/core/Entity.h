#pragma once
#include "Common.h"
#include "components/TransformComponent.h"

class PhysicsManager;

class Entity {
public:
	std::string name;

	std::vector<std::shared_ptr<EngineComponent>> components;
	std::vector<std::shared_ptr<Entity>> children;

	std::shared_ptr<TransformComponent> transform;

	Entity(const char* entityName, std::shared_ptr<PhysicsManager> _physicsManager) 
	{
		name = entityName; 
		transform = std::shared_ptr<TransformComponent>(new TransformComponent());
		transform->attachedEntity = std::shared_ptr<Entity>(this);
		physicsManager = _physicsManager;
	}
	Entity(const char* entityName)
	{
		name = entityName; 
		transform = std::shared_ptr<TransformComponent>(new TransformComponent());
		transform->attachedEntity = std::shared_ptr<Entity>(this);
	}
	~Entity() {}

	void AddComponent(EngineComponent* newComponent);

	// template method only works in .h file without round-about bs
	// any way to keep this in cpp?
	template <class T>
	std::shared_ptr<T> GetComponent()
	{
		for (int i = 0; i < components.size(); i++)
		{
			if(typeid(T) == typeid(*components.at(i)))
			{
				std::cout << "Found component: " << components.at(i)->name << std::endl;
				return(std::static_pointer_cast<T>(components.at(i)));
			}
		}
		std::cout << "component not found" << std::endl;
		return nullptr;
	}

	std::shared_ptr<Entity> AddEntity();
	std::shared_ptr<Entity> GetChild(int index);
	std::shared_ptr<Entity> GetChild(const char* name);

	std::shared_ptr<PhysicsManager> physicsManager;
	
	void initBehaviour();
	void startBehaviour();
	void earlyUpdateBehaviour(float deltaTime);
	void fixedUpdateBehaviour();
	void updateBehaviour(float deltaTime);
	void renderBehaviour(float deltaTime, glm::mat4 view);
	void uiBehaviour(float deltaTime);

private:
	int id;

	/*bool IsConvex(std::vector<vec3> &points, std::vector<int> &triangles, float threshold = 0.001)
	{
		for (unsigned long i = 0; i < triangles.size() / 3; i++)
		{

			vec3 Atmp = points[triangles[i * 3 + 0]];
			vec3 Btmp = points[triangles[i * 3 + 1]];
			vec3 Ctmp = points[triangles[i * 3 + 2]];

			btVector3 A(Atmp.x, Atmp.y, Atmp.z);
			btVector3 B(Btmp.x, Btmp.y, Btmp.z);
			btVector3 C(Ctmp.x, Ctmp.y, Ctmp.z);
			B -= A;
			C -= A;

			btVector3 BCNorm = B.cross(C).normalized();

			float checkPoint = btVector3(points[0].x - A.x(), points[0].y - A.y(), points[0].z - A.z()).dot(BCNorm);
			for (unsigned long j = 0; j < points.size(); j++)
			{

				float dist = btVector3(points[j].x - A.x(), points[j].y - A.y(), points[j].z - A.z()).dot(BCNorm);

				if (std::abs(checkPoint) > threshold & std::abs(dist) > threshold & checkPoint * dist < 0)
				{
					return false;
				}
			}
		}

		return true;
	}*/
};
