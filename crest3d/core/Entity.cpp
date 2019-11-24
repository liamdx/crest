#include "Entity.h"
#include "EngineManager.h"
#include "Example.h"

Entity::Entity(const char* entityName, EngineManager* _em) 
{
	engineManager = _em;
	name = entityName;
	transform = std::shared_ptr<TransformComponent>(new TransformComponent());
	transform->attachedEntity = std::shared_ptr<Entity>(this);
}

void Entity::ConsoleError(std::string error)
{
	engineManager->debug->console->Warn<Entity>(error.c_str(), id);
}


void Entity::AddComponent(EngineComponent* newComponent)
{
	bool canEmplace = true;
	for (unsigned int i = 0; i < components.size(); i++)
	{
		if (components[i]->name == newComponent->name)
		{
			canEmplace = false;
		}
	}
	if (canEmplace)
	{
		newComponent->SetId(engineManager->makeUniqueComponentID());
		components.emplace_back(newComponent);
	}
	else
	{
		std::string error = "Could not add ";
		error += typeid(newComponent).name();
		engineManager->debug->console->Warn<Entity>(error.c_str(), id);
		delete newComponent;
	}
}

void Entity::AddComponent(std::shared_ptr<EngineComponent> newComponent)
{
	bool canEmplace = true;
	for (unsigned int i = 0; i < components.size(); i++)
	{
		if (components[i]->name == newComponent->name)
		{
			canEmplace = false;
		}
	}
	if (canEmplace)
	{
		newComponent->SetId(engineManager->makeUniqueComponentID());
		components.emplace_back(newComponent);
	}
	else
	{
		std::string error = "Could not add ";
		error += typeid(newComponent).name();
		engineManager->debug->console->Warn<Entity>(error.c_str(), id);
	}
}

void Entity::initBehaviour()
{
	for (unsigned int i = 0; i < components.size(); i++)
	{
		components.at(i)->init();
	}
}

void Entity::startBehaviour()
{
	for (unsigned int i = 0; i < components.size(); i++)
	{
		components.at(i)->start();
	}
}

void Entity::earlyUpdateBehaviour(float deltaTime)
{
	for (unsigned int i = 0; i < components.size(); i++)
	{
		components.at(i)->earlyUpdate(deltaTime);
	}
}

void Entity::fixedUpdateBehaviour()
{
	for (unsigned int i = 0; i < components.size(); i++)
	{
		components.at(i)->fixedUpdate();
	}
}

void Entity::updateBehaviour(float deltaTime)
{
	transform->update(deltaTime);
	for (unsigned int i = 0; i < components.size(); i++)
	{
		components.at(i)->update(deltaTime);
	}
}

void Entity::renderBehaviour(float deltaTime, glm::mat4 view)
{
	for (unsigned int i = 0; i < components.size(); i++)
	{
		components.at(i)->render(deltaTime, view);
	}
}

void Entity::uiBehaviour(float deltaTime)
{
	for (unsigned int i = 0; i < components.size(); i++)
	{
		components.at(i)->ui(deltaTime);
	}
}

std::shared_ptr<Entity> Entity::AddEntity()
{
	children.emplace_back(new Entity("Entity", nullptr));
	return(children.at(children.size() - 1));
}

std::shared_ptr<Entity> Entity::GetChild(unsigned int index)
{
	if (index <= (children.size() - 1))
	{
		return(std::shared_ptr<Entity>(children.at(index)));
	}

	std::string error = "Could not find child";
	engineManager->debug->console->Warn<Entity>(error.c_str(), id);
	return nullptr;
}

std::shared_ptr<Entity> Entity::GetChild(const char* name)
{
	for (unsigned int i = 0; i < children.size(); i++)
	{
		if (children.at(i)->name == name)
		{
			return(std::shared_ptr<Entity>(children.at(i)));
		}
	}

	std::string error = "Could not find child : ";
	error += name;
	engineManager->debug->console->Warn<Entity>(error.c_str(), id);
	return nullptr;
}