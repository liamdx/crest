#pragma once
#include "Common.h"
#include "Entity.h"
#include "components/CameraComponent.h"
#include "components/lighting/DirectionalLightComponent.h"
#include "components/lighting/PointLightComponent.h"
#include "components/AnimatedModelComponent.h"
#include "PhysicsManager.h"
#include "AssetManager.h"

class Scene
{
public:
	std::shared_ptr<Entity> rootEntity;
	std::shared_ptr<PhysicsManager> physicsManager;
	std::shared_ptr<AssetManager> assetManager;
	std::string name;

	Scene(const char* _name, std::shared_ptr<PhysicsManager> _physicsManager);
	Scene(const char* _name, std::shared_ptr<PhysicsManager> _physicsManager, std::shared_ptr<AssetManager> _assetManager);

	std::shared_ptr<Entity> AddEntity();	
	std::shared_ptr<Entity> AddCameraEntity();
	std::shared_ptr<Entity> AddMeshEntity(std::shared_ptr<Mesh> mesh);
	std::shared_ptr<Entity> AddMeshEntity(std::shared_ptr<Mesh> mesh, std::string name);
	std::shared_ptr<Entity> AddModelEntity(std::shared_ptr<Model> model);
	std::shared_ptr<Entity> AddAnimatedModelEntity(std::shared_ptr<AnimatedModel> model);
	std::shared_ptr<Entity> AddDirectionalLightEntity();
	std::shared_ptr<Entity> AddPointLightEntity();


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
	void updateSceneLighting();
	std::shared_ptr<CameraComponent> sceneCamera;

	// helping to make stuff more SIMD freindly
	std::vector<std::shared_ptr<MeshComponent>> meshes;
	std::vector<std::shared_ptr<AnimatedModelComponent>> animatedModels;
	
	std::shared_ptr<ShaderComponent> defaultShader;
	std::shared_ptr<ShaderComponent> defaultAnimShader;

	// lighting stuff
	std::shared_ptr<DirectionalLightComponent> dirLightComponent;
	std::vector <std::shared_ptr<PointLightComponent>> pointLightComponents;

	float DEBUG_SPHERE_RADIUS;
private:
	void updateLightComponentsVector(std::shared_ptr<Entity> e);
	void bindDefaultTextures(std::shared_ptr<ShaderComponent> sc);
};