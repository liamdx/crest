#pragma once

#include "CrestCore.h"

class EngineManager;

class Example {
public:

	virtual ~Example() {};
	
	virtual void initBehaviour() {};
	virtual void startBehaviour() {};
	virtual void earlyUpdateBehaviour(float deltaTime) {};
	virtual void fixedUpdateBehaviour() {};
	virtual void updateBehaviour(float deltaTime) {};
	virtual void renderBehaviour(float deltaTime) {};
	virtual void uiBehaviour(float deltaTime) {};

	std::map<std::string, std::shared_ptr<Entity>> entities;
	std::map<std::string, std::shared_ptr<EngineComponent>> components;

	EngineManager* engineManager;
};