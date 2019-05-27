#include "Entity.h"

void Entity::AddComponent(EngineComponent* newComponent)
{
	bool canEmplace = true;
	for (int i = 0; i < components.size(); i++)
	{
		if (components[i]->name == newComponent->name)
		{
			canEmplace = false;
		}
	}
	if (canEmplace)
	{
		components.emplace_back(newComponent);
	}
	else
	{
		std::cout << "Entity: " << name << "already has a " << newComponent->name << std::endl;
		delete newComponent;
	}
	
}

void Entity::initBehaviour()
{
	for (int i = 0; i < components.size(); i++)
	{
		components.at(i)->init();
	}
}

void Entity::startBehaviour()
{
	for (int i = 0; i < components.size(); i++)
	{
		components.at(i)->start();
	}
}

void Entity::earlyUpdateBehaviour(float deltaTime)
{
	for (int i = 0; i < components.size(); i++)
	{
		components.at(i)->earlyUpdate(deltaTime);
	}
}

void Entity::updateBehaviour(float deltaTime)
{
	for (int i = 0; i < components.size(); i++)
	{
		components.at(i)->update(deltaTime);
	}
}

void Entity::renderBehaviour(float deltaTime)
{
	for (int i = 0; i < components.size(); i++)
	{
		components.at(i)->render(deltaTime);
	}
}


void Entity::uiBehaviour(float deltaTime)
{
	for (int i = 0; i < components.size(); i++)
	{
		components.at(i)->ui(deltaTime);
	}
}

std::shared_ptr<Entity> Entity::AddEntity()
{
	children.emplace_back(new Entity("Entity", physicsManager));
	return(children.at(children.size() - 1));
}

std::shared_ptr<Entity> Entity::GetChild(int index)
{
	if (index <= (children.size() - 1))
	{
		return(std::shared_ptr<Entity>(children.at(index)));
	}

	std::cout << "no child found at index " << index << std::endl;
	return nullptr;
}

std::shared_ptr<Entity> Entity::GetChild(const char* name)
{
	for(int i =0; i < children.size(); i++)
	{
		if (children.at(i)->name == name)
		{
			return(std::shared_ptr<Entity>(children.at(i)));
		}
	}
	

	std::cout << "no child found of name " << name << std::endl;
	return nullptr;
}
