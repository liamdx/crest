#pragma once
#include "Common.h"
#include "components/EngineComponent.h"

class Entity {
public:
	std::string name;

	std::vector<std::unique_ptr<EngineComponent>> components;


	Entity(const char* entityName) { name = entityName; }
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