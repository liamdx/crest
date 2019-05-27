#pragma once

#include "EngineComponent.h"

class DebugComponent : public EngineComponent
{
public:
	DebugComponent() { name = "DebugComponent"; };
	~DebugComponent() override {};

	void start() override;
	void earlyUpdate(float deltaTime) override;
	void update(float deltaTime) override;
	void ui(float deltaTime) override;

	void debugPrintSomething(const char* thing);
};