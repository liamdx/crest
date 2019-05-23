#pragma once
#include "Common.h"
#include "components/TransformComponent.h"

class Entity {
public:
	std::string name;

	std::vector<std::shared_ptr<EngineComponent>> components;
	std::vector<std::shared_ptr<Entity>> children;

	TransformComponent* transform = nullptr;

	Entity(const char* entityName) { name = entityName; transform = new TransformComponent(); }
	~Entity() {}

	void AddComponent(EngineComponent* newComponent);

	// template method only works in .h file without round-about bs
	// any way to keep this in cpp?
	template <class T>
	std::shared_ptr<T> GetComponent()
	{
		for (int i = 0; i < components.size(); i++)
		{
			//fix this, never finding the component
			if (typeid(components.at(i)).name == typeid(std::shared_ptr<T>))
			{
				return(std::static_pointer_cast<T>(components.at(i)));
			}
		}
		std::cout << "component not found" << std::endl;
		return nullptr;
	}

	void AddChild(std::shared_ptr<Entity> newChild);
	std::shared_ptr<Entity> GetChild(int index);
	std::shared_ptr<Entity> GetChild(const char* name);

	void initBehaviour();
	void startBehaviour();
	void earlyUpdateBehaviour();
	void updateBehaviour();
	void uiBehaviour();

private:
	int id;
};