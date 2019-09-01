#pragma once
#include "Common.h"
#include "components/TransformComponent.h"

class PhysicsManager;

class Entity {
public:

	struct EntityLoadInfo
	{
		std::string _name;
		std::vector<std::string> components;
	};

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

	void Delete();
	
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
				return(std::static_pointer_cast<T>(components.at(i)));
			}
		}
		// std::cout << "component not found" << std::endl;
		return nullptr;
	}

	std::shared_ptr<Entity> AddEntity();
	std::shared_ptr<Entity> GetChild(unsigned int index);
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
	// do we need this?
	int id;
};
