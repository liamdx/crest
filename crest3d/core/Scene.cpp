#include "Scene.h"
#include "components/MeshComponent.h"


Scene::Scene(const char* _name, std::shared_ptr<PhysicsManager> _physicsManager)
{
	physicsManager = _physicsManager;
	rootEntity = std::shared_ptr<Entity>(new Entity("root", physicsManager));
}


std::shared_ptr<Entity> Scene::AddEntity()
{
	return(rootEntity->AddEntity());
}


void childInit(std::shared_ptr<Entity> e) {
	e->initBehaviour();
	for (int i = 0; i < e->children.size(); i++)
	{
		childInit(e->children.at(i));
	}
}

void Scene::initBehaviour()
{
	childInit(rootEntity);
}

void childStart(std::shared_ptr<Entity> e) {
	e->startBehaviour();
	for (int i = 0; i < e->children.size(); i++)
	{
		childStart(e->children.at(i));
	}
}

void Scene::startBehaviour()
{
	childStart(rootEntity);
}

void childEarlyUpdate(std::shared_ptr<Entity> e, float deltaTime)
{
	e->earlyUpdateBehaviour(deltaTime);
	for (int i = 0; i < e->children.size(); i++)
	{
		childEarlyUpdate(e->children.at(i), deltaTime);
	}
}

void Scene::earlyUpdateBehaviour(float deltaTime)
{
	childEarlyUpdate(rootEntity, deltaTime);
}

void childFixedUpdate(std::shared_ptr<Entity> e )
{
	e->fixedUpdateBehaviour();
	for (int i = 0; i < e->children.size(); i++)
	{
		childFixedUpdate(e->children.at(i));
	}
}

void Scene::fixedUpdateBehaviour()
{
	childFixedUpdate(rootEntity);
}


void childUpdate(std::shared_ptr<Entity> e, float deltaTime)
{
	e->updateBehaviour(deltaTime);
	for (int i = 0; i < e->children.size(); i++)
	{
		childUpdate(e->children.at(i), deltaTime);
	}
}

void Scene::updateBehaviour(float deltaTime)
{
	childUpdate(rootEntity, deltaTime);
}

void childRender(std::shared_ptr<Entity> e, float deltaTime)
{
	e->renderBehaviour(deltaTime);
	for (int i = 0; i < e->children.size(); i++)
	{
		childRender(e->children.at(i), deltaTime);
	}
}

void Scene::renderBehaviour(float deltaTime)
{
	childRender(rootEntity, deltaTime);
}


void childUi(std::shared_ptr<Entity> e, float deltaTime)
{
	e->uiBehaviour(deltaTime);
	for (int i = 0; i < e->children.size(); i++)
	{
		childUi(e->children.at(i), deltaTime);
	}
}
void Scene::uiBehaviour(float deltaTime)
{
	childUi(rootEntity, deltaTime);
}

std::shared_ptr<Entity> Scene::AddCameraEntity()
{
	std::shared_ptr<Entity> e = rootEntity->AddEntity();
	e->AddComponent(new CameraComponent(e));
	sceneCamera = e->GetComponent<CameraComponent>();
	return e;
}


std::shared_ptr<Entity> Scene::AddMeshEntity(Mesh mesh)
{
	std::shared_ptr<Entity> e = std::shared_ptr<Entity>(new Entity("."));
	e->AddComponent(new MeshComponent(e, mesh));
	e->AddComponent(new ShaderComponent(e));
	return e;
}

std::shared_ptr<Entity> Scene::AddModelEntity(Model model)
{
	std::shared_ptr<Entity> e = rootEntity->AddEntity();
	e->name = "modelRoot";

	for(int i = 0; i < model.meshes.size(); i++)
	{
		e->children.emplace_back(AddMeshEntity(model.meshes.at(i)));
	}
	return e;
}
