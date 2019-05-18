#pragma once
#include "Common.h"
#include "components/TransformComponent.h"

class Entity {
public:
	std::string name;

	std::vector<std::unique_ptr<EngineComponent>> components;

	// TransformComponent* transform = nullptr;

	Entity(const char* entityName) { name = entityName; components.emplace_back(new TransformComponent()); }
	~Entity() {}

	void AddComponent(EngineComponent* newComponent);
	EngineComponent* GetComponent(const char* name);

	void startBehaviour();
	void earlyUpdateBehaviour();
	void updateBehaviour();
	void uiBehaviour();
	// void RemoveComponent() {}


private:
	int id;
};