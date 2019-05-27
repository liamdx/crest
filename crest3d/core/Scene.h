#pragma once
#include "Common.h"
#include "Entity.h"

class Scene
{
	std::shared_ptr<Entity> rootEntity;
	std::shared_ptr<PhysicsManager> physicsManager;
	std::string name;

	Scene(const char* _name, std::shared_ptr<PhysicsManager> _physicsManager);

	std::shared_ptr<Entity> AddEntity();

	void initBehaviour();
	void startBehaviour();
	void earlyUpdateBehaviour(float deltaTime);
	void updateBehaviour(float deltaTime);
	void renderBehaviour(float deltaTime);
	void uiBehaviour(float deltaTime);
};