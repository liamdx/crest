#pragma once
#include "Common.h"
#include "components/TransformComponent.h"

class Entity {
public:
	std::string name;

	std::vector<std::unique_ptr<EngineComponent>> components;
	std::vector<std::unique_ptr<Entity>> children;

	TransformComponent* transform = nullptr;

	Entity(const char* entityName) { name = entityName; transform = new TransformComponent(); }
	~Entity() {}

	void AddComponent(EngineComponent* newComponent);
	EngineComponent* GetComponent(const char* name);
	void AddChild(Entity* newChild);
	Entity* GetChild(int index);
	Entity* GetChild(const char* name);

	void startBehaviour();
	void earlyUpdateBehaviour();
	void updateBehaviour();
	void uiBehaviour();

private:
	int id;
};