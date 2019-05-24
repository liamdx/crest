
#pragma once

#include "EngineComponent.h"

class CameraComponent : public EngineComponent
{
public:
	CameraComponent() { name = "CameraComponent"; };
	~CameraComponent() override {};

	void init() override;
	void start() override;
	void earlyUpdate() override;
	void update() override;
	void ui() override;

};