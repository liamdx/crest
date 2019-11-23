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

	EngineManager(GLFWwindow* _window, Example* _example);
	~EngineManager() {};

	void initialise();

	std::unique_ptr<ShaderManager> shaderManager;
	std::unique_ptr<PhysicsManager> physicsManager;
	std::unique_ptr<AssetManager> assetManager;
	std::unique_ptr<Scene> scene;
	std::unique_ptr<InputManager> input;
	std::unique_ptr<Example> example;

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

private:
	const unsigned int currentSceneIndex = 0;
};
