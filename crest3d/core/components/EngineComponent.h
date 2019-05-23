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
	virtual void earlyUpdate() {};
	virtual void update() {};
	virtual void ui() {};
};