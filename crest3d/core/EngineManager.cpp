#include "EngineManager.h"
#include "Example.h"

EngineManager::EngineManager()
{
	initialise(800, 600);
	physicsManager = std::make_unique<PhysicsManager>();
	assetManager = std::make_unique<AssetManager>();
	shaderManager = std::make_unique<ShaderManager>();
	scene = std::unique_ptr<Scene>(new Scene("debugScene", this));
	input = std::unique_ptr<InputManager>(new InputManager(window));
	debug = std::make_unique<Debug>();
}


int EngineManager::initialise(int screenWidth, int screenHeight)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Failed to initalise SDL2 \n";
		return -1;
	}
	else
	{
		std::cout << "Successfully initialised SDL2 \n";
	}



	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	window = SDL_CreateWindow("Crest", 0, 0, 800, 600, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_MAXIMIZED );
	context = SDL_GL_CreateContext(window);
	SDL_GL_MakeCurrent(window, context);
	
	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initalise GLEW \n";
		return -1;
	}
	else
	{
		std::cout << "Successfully initialised GLEW \n";
	}
	//Enable depth
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_MULTISAMPLE);
	glCullFace(GL_BACK);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	YSE::System().init();
	return 1;
}

void EngineManager::initialiseExample(Example* _example)
{
	example = std::unique_ptr<Example>(_example);
}


unsigned int EngineManager::makeUniqueComponentID()
{
	unsigned int newId = componentIds.size();
	componentIds.emplace_back(newId);
	return(newId);
}

unsigned int EngineManager::makeUniqueEntityID()
{
	unsigned int newId = entityIds.size();
	entityIds.emplace_back(newId);
	return(newId);
}

std::shared_ptr<Entity> EngineManager::AddEntity()
{
	unsigned int entityID = makeUniqueEntityID();
	std::string name = "Entity: " + entityID;
	std::shared_ptr<Entity> e = std::make_shared<Entity>(name.c_str(), this, scene->rootEntity);
	e->transform->attachedEntity = e;
	scene->rootEntity->AddChild(e);
	e->SetId(entityID);
	return e;
}

std::shared_ptr<Entity> EngineManager::AddEntity(std::shared_ptr<Entity> parent)
{
	unsigned int entityID = makeUniqueEntityID();
	std::string name = "Entity: " + entityID;
	std::shared_ptr<Entity> e = std::make_shared<Entity>(name.c_str(), this, parent);
	e->transform->attachedEntity = e;
	parent->AddChild(e);
	e->SetId(entityID);
	return e;
}


std::shared_ptr<Entity> EngineManager::AddEntity(const char* name)
{
	unsigned int entityID = makeUniqueEntityID();
	std::shared_ptr<Entity> e = std::make_shared<Entity>(name, this, scene->rootEntity);
	e->transform->attachedEntity = e;
	scene->rootEntity->AddChild(e);
	e->SetId(entityID);
	return e;
}

std::shared_ptr<Entity> EngineManager::AddEntity(std::shared_ptr<Entity> parent, const char* name)
{
	unsigned int entityID = makeUniqueEntityID();
	std::shared_ptr<Entity> e = std::make_shared<Entity>(name, this, parent);
	e->transform->attachedEntity = e;
	parent->AddChild(e);
	e->SetId(entityID);
	return e;
}



std::shared_ptr<Entity> EngineManager::AddCameraEntity()
{
	std::shared_ptr<Entity> e = AddEntity("Camera Entity");
	e->engineManager = this;
	e->AddComponent(new CameraComponent(e));
	scene->sceneCamera = e->GetComponent<CameraComponent>();
	scene->sceneCamera->SetId(makeUniqueComponentID());
	Debug::Log<EngineManager>("Creating Camera Entity");
	return e;
}

std::shared_ptr<Entity> EngineManager::AddMeshEntity(std::shared_ptr<Mesh> mesh)
{
	std::shared_ptr<Entity> e = AddEntity("Mesh Entity");
	e->AddComponent(new MeshComponent(e, mesh));
	e->SetId(makeUniqueEntityID());
	auto mc = e->GetComponent<MeshComponent>();
	mc->SetId(makeUniqueComponentID());
	//debug->console->Log<EngineManager>("Creating Mesh Entity");
	Debug::Log<EngineManager>("Creating Mesh Entity");
	return e;
}

std::shared_ptr<Entity> EngineManager::AddMeshEntity(std::shared_ptr<Entity> parent, std::shared_ptr<Mesh> mesh)
{
	std::shared_ptr<Entity> e = AddEntity(parent,"Mesh Entity");
	e->AddComponent(new MeshComponent(e, mesh));
	e->SetId(makeUniqueEntityID());
	auto mc = e->GetComponent<MeshComponent>();
	mc->SetId(makeUniqueComponentID());
	Debug::Log<EngineManager>("Creating Mesh Entity");
	return e;
}

std::shared_ptr<Entity> EngineManager::AddMeshEntity(std::shared_ptr<Mesh> mesh, std::string name)
{
	std::shared_ptr<Entity> e = AddEntity(name.c_str());
	e->AddComponent(new MeshComponent(e, mesh));
	e->SetId(makeUniqueEntityID());
	auto mc = e->GetComponent<MeshComponent>();
	if (mc != nullptr)
	{
		scene->meshes.emplace_back(e->GetComponent<MeshComponent>());
	}
	Debug::Log<EngineManager>("Creating Mesh Entity");
	return e;
}

std::shared_ptr<Entity> EngineManager::AddMeshEntity(std::shared_ptr<Entity> parent, std::shared_ptr<Mesh> mesh, std::string name)
{
	std::shared_ptr<Entity> e = AddEntity(parent,name.c_str());
	e->AddComponent(new MeshComponent(e, mesh));
	e->SetId(makeUniqueEntityID());
	auto mc = e->GetComponent<MeshComponent>();
	if (mc != nullptr)
	{
		scene->meshes.emplace_back(e->GetComponent<MeshComponent>());
	}
	Debug::Log<EngineManager>("Creating Mesh Entity");
	return e;
}


std::shared_ptr<Entity> EngineManager::AddModelEntity(std::shared_ptr<Model> model)
{
	std::shared_ptr<Entity> e = AddEntity();
	e->engineManager = this;
	e->name = model->name + std::to_string(e->GetID());
	e->SetId(makeUniqueEntityID());
	for (int i = 0; i < model->meshes.size(); i++)
	{
		std::shared_ptr<Entity> newE = AddMeshEntity(e,model->meshes.at(i), std::to_string(i));
		newE->transform->setParent(e->transform);
	}
	Debug::Log<EngineManager>("Creating Model Entity");
	return e;
}

std::shared_ptr<Entity> EngineManager::AddAnimatedModelEntity(std::shared_ptr<AnimatedModel> model)
{
	std::shared_ptr<Entity> e = AddEntity();
	e->engineManager = this;
	e->SetId(makeUniqueEntityID());
	e->name = "AnimModel" + std::to_string(e->GetID());
	e->AddComponent(new AnimatedModelComponent(e, model));
	auto amc = e->GetComponent<AnimatedModelComponent>();
	amc->getBoneShaderIDLocations(shaderManager->defaultAnimShader);
	scene->animatedModels.emplace_back(amc);
	Debug::Log<EngineManager>("Creating Animated Model Entity");
	return e;
}

std::shared_ptr<Entity> EngineManager::AddDirectionalLightEntity()
{
	std::shared_ptr<Entity> e = AddEntity();
	e->engineManager = this;
	e->name = "Directional Light";
	e->SetId(makeUniqueEntityID());
	e->AddComponent(new DirectionalLightComponent(e));
	auto dl = e->GetComponent<DirectionalLightComponent>();
	Debug::Log<EngineManager>("Creating Directional Light Entity");
	return(e);
}

std::shared_ptr<Entity> EngineManager::AddPointLightEntity()
{
	std::shared_ptr<Entity> e = AddEntity();
	e->engineManager = this;
	std::stringstream ss;
	ss << "Point Light " << (scene->pointLightComponents.size() + 1);
	std::string s = ss.str();
	e->name = s;
	e->SetId(makeUniqueEntityID());
	e->AddComponent(new PointLightComponent(e));
	auto plc = e->GetComponent<PointLightComponent>();
	scene->pointLightComponents.emplace_back(plc);
	Debug::Log<EngineManager>("Creating Point Light Entity");
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
	while (it != example->components.end())
	{
		unsigned int componentId = it->second->id;
		if (componentId == _id)
		{
			componentToDelete = it->first;
			shouldDelete = true;
		}
		it++;
	}
	if (shouldDelete)
	{
		example->components.erase(componentToDelete);
		return;
	}
}

std::shared_ptr<Entity> EngineManager::getEntity(std::shared_ptr<Entity> e, unsigned int _id)
{
	if (e->GetID() == _id)
	{
		return e;
	}
	else
	{
		if (e->children.size() > 0)
		{
			for (unsigned int i = 0; i < e->children.size(); i++)
			{
				if(e->children.at(i)->GetID() == _id)
				{
					return e->children.at(i);
				}
			}
			for(unsigned int i = 0; i < e->children.size(); i++)
			{
				getEntity(e->children.at(i), _id);
			}
		}
	}
}

void EngineManager::DeleteEntity(unsigned int entityId)
{
	std::shared_ptr<Entity> e = nullptr;
	e = getEntity(scene->rootEntity, entityId);
	
	std::cout << "Entity num components before deletion : " << std::to_string(e->components.size()) << std::endl;
	if (e != nullptr)
	{
		for (int i = 0; i < e->components.size(); i++)
		{
			DeleteComponent(e->components.at(i)->id);
			e->components.clear();
		}
	}
	std::cout << "Entity num components after deletion : " << std::to_string(e->components.size()) << std::endl;

	for(int i = 0; i < e->children.size(); i++)
	{
		for (int j = 0; j < e->children.at(i)->components.size(); j++)
		{
			DeleteComponent(e->children.at(i)->components.at(j)->id);
		}
		e->children.at(i)->components.clear();
	}

	std::string entityName = "";
	for(auto var : example->entities)
	{
		if(var.second->GetID() == entityId)
		{
			entityName = var.first;
		}
	}

	if(entityName != "")
	{
		example->entities.erase(entityName);
	}
	e->parent->RemoveChild(entityId);
	e->ClearChildren();
}

void EngineManager::DeleteComponent(unsigned int componentId)
{
	if (scene->dirLightComponent != nullptr && scene->dirLightComponent->id == componentId)
	{
		scene->dirLightComponent = nullptr;
	}

	for (int i = 0; i < scene->pointLightComponents.size(); i++)
	{
		auto plc = scene->pointLightComponents.at(i);
		if (plc->id == componentId)
		{
			scene->pointLightComponents.erase(scene->pointLightComponents.begin() + i);
			break;
		}
	}

	for (int i = 0; i < scene->meshes.size(); i++)
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

void EngineManager::shutdown()
{
	
}
