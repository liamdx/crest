#pragma once

#include "EngineComponent.h"

class DebugComponent : public EngineComponent
{
public:
	DebugComponent() { name = "DebugComponent"; };
	~DebugComponent() override {};

	void start() override;
	void earlyUpdate() override;
	void update() override;
	void ui() override;
};