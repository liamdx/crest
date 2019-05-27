#pragma once
#include "Common.h"

class Entity;
class EngineComponent {
public:
	const char* name;
	std::shared_ptr<Entity> attachedEntity = nullptr;

	EngineComponent(const char* componentName = "EngineComponent") { name = componentName; }
	virtual ~EngineComponent() {};
	virtual void init() {};
	virtual void start() {};
	virtual void earlyUpdate(float deltaTime) {};
	virtual void update(float deltaTime) {};
	virtual void fixedUpdate() {};
	virtual void render(float deltaTime) {};
	virtual void ui(float deltaTime) {};
};