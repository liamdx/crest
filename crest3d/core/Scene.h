#pragma once
#include "Common.h"
#include "Entity.h"
#include "components/CameraComponent.h"
#include "components/lighting/DirectionalLightComponent.h"
#include "components/lighting/PointLightComponent.h"
#include "components/AnimatedModelComponent.h"
#include "components/MeshComponent.h"
#include "AssetManager.h"
#include "ShaderManager.h"
#include "PhysicsManager.h"

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
	void renderBehaviour(float deltaTime, std::shared_ptr<ShaderComponent> meshShader, std::shared_ptr<ShaderComponent> animShader);
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
	// lighting stuff
	std::shared_ptr<DirectionalLightComponent> dirLightComponent;
	std::vector <std::shared_ptr<PointLightComponent>> pointLightComponents;

	float DEBUG_SPHERE_RADIUS;
private:
	void updateLightComponentsVector(std::shared_ptr<Entity> e);
	void bindDefaultTextures(std::shared_ptr<ShaderComponent> sc);
};