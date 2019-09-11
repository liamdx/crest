#pragma once
#include "Common.h"

class Entity;
class EngineComponent {
public:
	const char* name;
	unsigned int id;
	std::shared_ptr<Entity> attachedEntity = nullptr;

	EngineComponent(const char* componentName = "EngineComponent") { name = componentName; }
	virtual ~EngineComponent() {};
	virtual void init() {};
	virtual void start() {};
	virtual void earlyUpdate(float deltaTime) {};
	virtual void update(float deltaTime) {};
	virtual void fixedUpdate() {};
	virtual void render(float deltaTime, glm::mat4 view) {};
	virtual void ui(float deltaTime) {};

	inline void SetId(unsigned int newId) { id = newId; }
};