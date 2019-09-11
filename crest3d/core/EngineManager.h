#pragma once

#include "ShaderManager.h"
#include "PhysicsManager.h"
#include "AssetManager.h"
#include "Scene.h"
#include "InputManager.h"

class Example;

class EngineManager
{
public:

	EngineManager(std::shared_ptr<Example> _example);
	~EngineManager() {};

	void initialise();
	
	std::shared_ptr<ShaderManager> shaderManager = nullptr;
	std::shared_ptr<PhysicsManager> physicsManager = nullptr;
	std::shared_ptr<AssetManager> assetManager = nullptr;
	std::shared_ptr<Scene> scene = nullptr;
	std::shared_ptr<InputManager> input = nullptr;
	std::shared_ptr<Example> example = nullptr;
	std::shared_ptr<GLFWwindow> window = nullptr;
	// need to rewrite input manager to allow for SDL window
	// std::unique_ptr<SDLWindow> window;

	std::vector<unsigned int> componentIds;
	std::vector<unsigned int> entityIds;

	unsigned int makeUniqueEntityID();
	unsigned int makeUniqueComponentID();

	std::shared_ptr<Entity> AddEntity();
	std::shared_ptr<Entity> AddCameraEntity();
	std::shared_ptr<Entity> AddMeshEntity(std::shared_ptr<Mesh> mesh);
	std::shared_ptr<Entity> AddMeshEntity(std::shared_ptr<Mesh> mesh, std::string name);
	std::shared_ptr<Entity> AddModelEntity(std::shared_ptr<Model> model);
	std::shared_ptr<Entity> AddAnimatedModelEntity(std::shared_ptr<AnimatedModel> model);
	std::shared_ptr<Entity> AddDirectionalLightEntity();
	std::shared_ptr<Entity> AddPointLightEntity();

	void DeleteEntity(unsigned int entityId);
	void DeleteComponent(unsigned int componentId);

	void deleteComponentInExample(unsigned int _id);
	void deleteComponentInScene(std::shared_ptr<Entity> e, unsigned int _id);

	std::shared_ptr<Entity> getEntity(std::shared_ptr<Entity> e, unsigned int _id);
};
