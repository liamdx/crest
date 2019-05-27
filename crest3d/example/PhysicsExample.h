#pragma once
#include "Example.h"
class PhysicsExample : public Example
{
public:
	PhysicsExample(GLFWwindow* _window);
	~PhysicsExample() override {};

	void initBehaviour() override;
	void startBehaviour() override;
	void earlyUpdateBehaviour(float deltaTime) override;
	void fixedUpdateBehaviour() override;
	void updateBehaviour(float deltaTime) override;
	void renderBehaviour(float deltaTime) override;
	void uiBehaviour(float deltaTime) override;

private:
	std::shared_ptr<PhysicsManager> pm;
	std::unique_ptr<Scene> scene;

	std::shared_ptr<Entity> levelEntity;
	std::shared_ptr<Entity> cyborgEntity;
	std::shared_ptr<Entity> cameraEntity;
};