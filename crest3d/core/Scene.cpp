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
	// update every entity with a shader
	updateShaderProjections(rootEntity);
	physicsManager->setProjection(sceneCamera->GetProjectionMatrix());
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
	physicsManager->update(deltaTime);
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

void childRender(std::shared_ptr<Entity> e, float deltaTime, glm::mat4 view)
{
	e->renderBehaviour(deltaTime, view);
	for (int i = 0; i < e->children.size(); i++)
	{
		childRender(e->children.at(i), deltaTime, view);
	}
}

void Scene::renderBehaviour(float deltaTime)
{
	glm::mat4 view = sceneCamera->GetViewMatrix();
	childRender(rootEntity, deltaTime, view);


	physicsManager->setView(view);
	// clear the depth buffer so it draws in front;
	glClear(GL_DEPTH_BUFFER_BIT);
	physicsManager->render(deltaTime);
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
	std::shared_ptr<Entity> e = std::shared_ptr<Entity>(new Entity(".", physicsManager));
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
		std::shared_ptr<Entity> newE = AddMeshEntity(model.meshes.at(i));
		newE->transform->parent = e->transform;
		e->children.emplace_back(newE);
	}
	return e;
}

void Scene::updateShaderProjections(std::shared_ptr<Entity> e)
{
	std::shared_ptr<ShaderComponent> sc = e->GetComponent<ShaderComponent>();
	
	if(sc != nullptr)
		sc->setProjection(sceneCamera->GetProjectionMatrix());

	for(int i = 0; i < e->children.size(); i++)
	{
		updateShaderProjections(e->children.at(i));
	}
}