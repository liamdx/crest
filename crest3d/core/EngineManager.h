#pragma once


#include "Scene.h"
#include "InputManager.h"
#include "Debug.h"

class Example;

class EngineManager
{
public:

	EngineManager();
	~EngineManager();

	int initialise(int screenWidth, int screenHeight);
	void initialiseExample(Example* _example);
	void shutdown();

	std::unique_ptr<ShaderManager> shaderManager;
	std::unique_ptr<PhysicsManager> physicsManager;
	std::unique_ptr<AssetManager> assetManager;
	std::unique_ptr<Scene> scene;
	std::shared_ptr<InputManager> input;
	std::unique_ptr<Example> example;
	std::unique_ptr<Debug> debug;

	// probably should be made generic (likely wil switch to SDL at somepoint) 
	GLFWwindow* window;


	std::vector<unsigned int> componentIds;
	std::vector<unsigned int> entityIds;

	unsigned int makeUniqueEntityID();
	unsigned int makeUniqueComponentID();

	std::shared_ptr<Entity> AddEntity();
	std::shared_ptr<Entity> AddEntity(const char* name);
	std::shared_ptr<Entity> AddEntity(std::shared_ptr<Entity> parent);
	std::shared_ptr<Entity> AddEntity(std::shared_ptr<Entity> parent, const char* name);
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
