#pragma once

#include "CrestCore.h"

class Example {
public:

	virtual ~Example() {};
	void initialise(std::shared_ptr<Example> e) {
		//engineManager = std::make_unique<EngineManager>(e);
		}
	virtual void initBehaviour() {};
	virtual void startBehaviour() {};
	virtual void earlyUpdateBehaviour(float deltaTime) {};
	virtual void fixedUpdateBehaviour() {};
	virtual void updateBehaviour(float deltaTime) {};
	virtual void renderBehaviour(float deltaTime) {};
	virtual void uiBehaviour(float deltaTime) {};

	std::map<std::string, std::shared_ptr<Entity>> entities;
	std::map<std::string, std::shared_ptr<EngineComponent>> components;

	// bstd::unique_ptr<EngineManager> engineManager;
};