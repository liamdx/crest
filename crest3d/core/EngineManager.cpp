#include "EngineManager.h"
#include "Example.h"

EngineManager::EngineManager(std::shared_ptr<Example> _example)
{
	example = _example;
	physicsManager = std::shared_ptr<PhysicsManager>(new PhysicsManager());
	assetManager = std::make_shared<AssetManager>();
	shaderManager = std::make_shared<ShaderManager>();
	scene = std::shared_ptr<Scene>(new Scene("debugScene", physicsManager, assetManager));
	input = std::shared_ptr<InputManager>(new InputManager(window.get()));
}


unsigned int EngineManager::makeUniqueComponentID()
{
	auto newId = componentIds.size();
	componentIds.emplace_back(newId);
	return(newId);
}

unsigned int EngineManager::makeUniqueEntityID()
{
	auto newId = entityIds.size();
	entityIds.emplace_back(newId);
	return(newId);
}


std::shared_ptr<Entity> EngineManager::AddCameraEntity()
{
	std::shared_ptr<Entity> e = scene->rootEntity->AddEntity();
	e->AddComponent(new CameraComponent(e));
	scene->sceneCamera = e->GetComponent<CameraComponent>();
	scene->sceneCamera->SetId(makeUniqueComponentID());
	e->SetId(makeUniqueEntityID());
	return e;
}


std::shared_ptr<Entity> EngineManager::AddMeshEntity(std::shared_ptr<Mesh> mesh)
{
	std::shared_ptr<Entity> e = std::shared_ptr<Entity>(new Entity("Mesh Entity"));
	e->AddComponent(new MeshComponent(e, mesh));
	e->SetId(makeUniqueEntityID());
	auto mc = e->GetComponent<MeshComponent>();
	mc->SetId(makeUniqueComponentID());
	return e;
}

std::shared_ptr<Entity> EngineManager::AddMeshEntity(std::shared_ptr<Mesh> mesh, std::string name)
{
	std::shared_ptr<Entity> e = std::shared_ptr<Entity>(new Entity(name.c_str()));
	e->AddComponent(new MeshComponent(e, mesh));
	e->SetId(makeUniqueEntityID());
	auto mc = e->GetComponent<MeshComponent>();
	mc->SetId(makeUniqueComponentID());
	if (mc != nullptr)
	{
		scene->meshes.emplace_back(e->GetComponent<MeshComponent>());
	}

	return e;
}


std::shared_ptr<Entity> EngineManager::AddModelEntity(std::shared_ptr<Model> model)
{
	std::shared_ptr<Entity> e = scene->rootEntity->AddEntity();
	e->name = model->name;
	e->SetId(makeUniqueEntityID());
	for (int i = 0; i < model->meshes.size(); i++)
	{
		std::shared_ptr<Entity> newE = AddMeshEntity(model->meshes.at(i), std::to_string(i));
		newE->transform->parent = e->transform;
		e->children.emplace_back(newE);
	}
	return e;
}

std::shared_ptr<Entity> EngineManager::AddAnimatedModelEntity(std::shared_ptr<AnimatedModel> model)
{
	std::shared_ptr<Entity> e = scene->rootEntity->AddEntity();
	e->SetId(makeUniqueEntityID());
	e->name = model->directory;
	e->AddComponent(new AnimatedModelComponent(e, model));
	auto amc = e->GetComponent<AnimatedModelComponent>();
	amc->SetId(makeUniqueComponentID());
	amc->getBoneShaderIDLocations(shaderManager->defaultAnimShader);
	scene->animatedModels.emplace_back(amc);
	return e;
}


std::shared_ptr<Entity> EngineManager::AddDirectionalLightEntity()
{
	std::shared_ptr<Entity> e = scene->rootEntity->AddEntity();
	e->name = "Directional Light";
	e->SetId(makeUniqueEntityID());
	e->AddComponent(new DirectionalLightComponent(e));
	auto dl = e->GetComponent<DirectionalLightComponent>();
	dl->SetId(makeUniqueComponentID());
	return(e);
}

std::shared_ptr<Entity> EngineManager::AddPointLightEntity()
{
	std::shared_ptr<Entity> e = scene->rootEntity->AddEntity();
	std::stringstream ss;
	ss << "Point Light " << (scene->pointLightComponents.size() + 1);
	std::string s = ss.str();
	e->name = s;
	e->SetId(makeUniqueEntityID());
	e->AddComponent(new PointLightComponent(e));
	auto plc = e->GetComponent<PointLightComponent>();
	plc->SetId(makeUniqueComponentID());
	scene->pointLightComponents.emplace_back(plc);
	return(e);
}

void EngineManager::deleteComponentInScene(std::shared_ptr<Entity> e, unsigned int _id)
{
	bool shouldDelete = false;
	int indexToRemove = 0;
	for (int i = 0; i < e->components.size(); i++)
	{
		auto c = e->components.at(i);
		if (c->id == _id)
		{
			indexToRemove = i;
		}
	}
	if (shouldDelete)
	{
		e->components.erase(e->components.begin() + indexToRemove);
		return;
	}
	else
	{
		for (int i = 0; i < e->children.size(); i++)
		{
			deleteComponentInScene(e->children.at(i), _id);
		}
	}

}

void EngineManager::deleteComponentInExample(unsigned int _id)
{
	std::map<std::string, std::shared_ptr<EngineComponent>>::iterator it = example->components.begin();
	std::string componentToDelete = "";
	bool shouldDelete = false;
	while(it != example->components.end())
	{
		unsigned int componentId = it->second->id;
		if(componentId == _id)
		{
			componentToDelete = it->first;
			shouldDelete = true;
		}
	}
	if(shouldDelete)
	{
		example->components.erase(componentToDelete);
	}
	
}

std::shared_ptr<Entity> EngineManager::getEntity(std::shared_ptr<Entity> e, unsigned int _id)
{
	if (e->id == _id)
	{
		return e;
	}
	else
	{
		for (unsigned int i = 0; i < e->children.size(); i++)
		{
			getEntity(e->children.at(i), _id);
		}
	}
}


void EngineManager::DeleteEntity(unsigned int entityId)
{
	std::shared_ptr<Entity> e = nullptr;
	e = getEntity(scene->rootEntity, entityId);
	std::cout << "Entity num components before deletion : " << std::to_string(e->components.size()) << std::endl;
	if(e != nullptr)
	{
		for(int i = 0; i < e->components.size(); i++)
		{
			DeleteComponent(e->components.at(i)->id);
		}
	}
	std::cout << "Entity num components after deletion : " << std::to_string(e->components.size()) << std::endl;
}


void EngineManager::DeleteComponent(unsigned int componentId)
{
	if(scene->dirLightComponent->id == componentId)
	{
		scene->dirLightComponent = nullptr;
	}

	for(int i = 0; i < scene->pointLightComponents.size(); i++)
	{
		auto plc = scene->pointLightComponents.at(i);
		if (plc->id == componentId)
		{
			scene->pointLightComponents.erase(scene->pointLightComponents.begin() + i);
			break;
		}
	}
	
	for(int i = 0; i < scene->meshes.size(); i++)
	{
		auto mc = scene->meshes.at(i);
		if (mc->id == componentId)
		{
			scene->meshes.erase(scene->meshes.begin() + i);
			break;
		}
	}

	for (int i = 0; i < scene->animatedModels.size(); i++)
	{
		auto amc = scene->animatedModels.at(i);
		if (amc->id == componentId)
		{
			scene->animatedModels.erase(scene->animatedModels.begin() + i);
			break;
		}
	}
	
	deleteComponentInScene(scene->rootEntity, componentId);
	deleteComponentInExample(componentId);
}

