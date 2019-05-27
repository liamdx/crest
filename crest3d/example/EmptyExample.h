#pragma once
#include "Example.h"
class EmptyExample : public Example
{
	EmptyExample(GLFWwindow* _window);
	~EmptyExample() override {};

	void initBehaviour() override;
	void startBehaviour() override;
	void earlyUpdateBehaviour(float deltaTime) override;
	void fixedUpdateBehaviour() override;
	void updateBehaviour(float deltaTime) override;
	void renderBehaviour(float deltaTime) override;
	void uiBehaviour(float deltaTime) override;
};