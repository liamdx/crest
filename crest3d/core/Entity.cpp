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

void Entity::earlyUpdateBehaviour()
{
	for (int i = 0; i < components.size(); i++)
	{
		components.at(i)->earlyUpdate();
	}
}

void Entity::updateBehaviour()
{
	for (int i = 0; i < components.size(); i++)
	{
		components.at(i)->update();
	}
}

void Entity::uiBehaviour()
{
	for (int i = 0; i < components.size(); i++)
	{
		components.at(i)->ui();
	}
}

EngineComponent* Entity::GetComponent(const char* componentName)
{
	for (int i = 0; i < components.size(); i++)
	{
		if (components.at(i)->name == componentName)
		{
			return(components.at(i).get());
		}
	}
}

void Entity::AddChild(Entity* newChild)
{
	children.emplace_back(newChild);
}

Entity* Entity::GetChild(int index)
{
	if (index <= (children.size() - 1))
	{
		return(children.at(index).get());
	}

	std::cout << "no child found at index " << index << std::endl;
	return nullptr;
}

Entity* Entity::GetChild(const char* name)
{
	for (int i = 0; i < children.size(); i++)
	{
		if (children.at(i)->name == name)
		{
			return(children.at(i).get());
		}
	}
	return nullptr;
}