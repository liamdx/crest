#pragma once
#include "Common.h"
#include "Entity.h"
#include "components/CameraComponent.h"
#include "gfx/Model.h"
#include "PhysicsManager.h"

class Scene
{
public:
	std::shared_ptr<Entity> rootEntity;
	std::shared_ptr<PhysicsManager> physicsManager;
	std::string name;

	Scene(const char* _name, std::shared_ptr<PhysicsManager> _physicsManager);

	std::shared_ptr<Entity> AddEntity();	
	std::shared_ptr<Entity> AddCameraEntity();
	std::shared_ptr<Entity> AddMeshEntity(Mesh mesh);
	std::shared_ptr<Entity> AddMeshEntity(Mesh mesh, std::string name);
	std::shared_ptr<Entity> AddModelEntity(Model model);


	void initBehaviour();
	void startBehaviour();
	void earlyUpdateBehaviour(float deltaTime);
	void fixedUpdateBehaviour();
	void updateBehaviour(float deltaTime);
	void renderBehaviour(float deltaTime);
	void uiBehaviour(float deltaTime);


	void updateShaderProjections(std::shared_ptr<Entity> e);
	std::shared_ptr<CameraComponent> sceneCamera;

private:

	
};