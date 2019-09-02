#pragma once
#include "PhysicsManager.h"
#include "AssetManager.h"
#include "Scene.h"
#include "InputManager.h"

class GameManager
{
public:
	std::unique_ptr<PhysicsManager> physicsManager;
	std::unique_ptr<AssetManager> assetManager;
	std::unique_ptr<Scene> scene;
	std::shared_ptr<InputManager> input;
	s
	
};
