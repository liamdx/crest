#pragma once
#include "Common.h"
#include "Entity.h"
#include "components/CameraComponent.h"
#include "components/lighting/DirectionalLightComponent.h"
#include "components/lighting/PointLightComponent.h"
#include "components/AnimatedModelComponent.h"
#include "components/MeshComponent.h"
#include "AssetManager.h"
#include "gfx/ShaderManager.h"
#include "PhysicsManager.h"
#include "components/ParticleSystemComponent.h"

class Scene
{
public:
	std::shared_ptr<Entity> rootEntity;

	EngineManager* engineManager;
	std::string name;

	Scene(const char* _name, EngineManager* em);

	void initBehaviour();
	void startBehaviour();
	void earlyUpdateBehaviour(float deltaTime);
	void fixedUpdateBehaviour();
	void updateBehaviour(float deltaTime);
	void renderBehaviour(float deltaTime);
	void uiBehaviour(float deltaTime);


	void updateShaderProjections(std::shared_ptr<Entity> e);

	// might move this to a lighting manager
	void updateShaderLightSources(std::shared_ptr<Entity> e);
	void updateShaderComponentLightSources(std::shared_ptr<ShaderComponent> sc);
	void updateDrawables();
	void updateSceneLighting();
	// the concept of a scene camera will die with renderer
	// .. need a distinction between a real camera to be rendered.
	// and a proxy camera that can be used as a virtual view point in the scene. 
	std::shared_ptr<CameraComponent> sceneCamera;
	
	// scene keeps references to every drawable for renderer. 
	std::vector<std::shared_ptr<MeshComponent>> meshes;
	std::vector<std::shared_ptr<AnimatedModelComponent>> animatedModels;
	std::vector<std::shared_ptr<ParticleSystemComponent>> particleSystems;
	std::shared_ptr<DirectionalLightComponent> dirLightComponent;
	std::vector <std::shared_ptr<PointLightComponent>> pointLightComponents;


	template<typename T>
	std::vector<std::shared_ptr<T>> FindComponentsInScene();

	
	
	float DEBUG_SPHERE_RADIUS;
private:

	
	void updateLightComponentsVector(std::shared_ptr<Entity> e);
	void bindDefaultTextures(std::shared_ptr<ShaderComponent> sc);
};
