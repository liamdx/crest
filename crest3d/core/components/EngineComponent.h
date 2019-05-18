#pragma once

class EngineComponent {
public:
	const char* name;
	EngineComponent(const char* componentName = "EngineComponent") { name = componentName; }
	virtual ~EngineComponent() {};
	virtual void start() {};
	virtual void earlyUpdate() {};
	virtual void update() {};
	virtual void ui() {};
};