#include "Entity.h"

void Entity::AddComponent(EngineComponent* newComponent)
{
	components.emplace_back(newComponent);
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


