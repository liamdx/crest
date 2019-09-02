#pragma once
#include "PhysicsManager.h"
#include "AssetManager.h"
#include "Scene.h"
#include "InputManager.h"

class EngineManager
{
public:
	std::unique_ptr<PhysicsManager> physicsManager;
	std::unique_ptr<AssetManager> assetManager;
	std::vector<std::unique_ptr<Scene>> scenes;
	std::unique_ptr<InputManager> input;
	
};
