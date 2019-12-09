#include "Entity.h"
#include "EngineManager.h"
#include "Example.h"

Entity::Entity(const char* entityName, EngineManager* _em, std::shared_ptr<Entity> e)
{
	engineManager = _em;
	state = UpdateState::fullRate;
	name = entityName;
	transform = std::shared_ptr<TransformComponent>(new TransformComponent());
	parent = e;
	quarterRateCounter = 0;
	halfRateCounter = 0;
	quarterRateTIme = 0.0f;
	halfRateTime = 0.0f;
	if(parent != nullptr)
	{
		transform->setParent(parent->transform);
	}
	else
	{
		transform->setParent(nullptr);
	}
	
}

void Entity::ConsoleError(std::string error)
{

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
		newComponent->init();
		newComponent->start();
		components.emplace_back(newComponent);
		std::string message;
		message = "ID: " + std::to_string(id) + " successfully added a " + typeid(*newComponent).name() + "\n";
		Debug::Log<Entity>(message.c_str());
	}
	else
	{
		std::string message;
		message = "ID: " + std::to_string(id) + " could not add a " + typeid(*newComponent).name() + " to the Entity\n";
		Debug::Warn<Entity>(message.c_str());
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
		newComponent->init();
		newComponent->start();
		components.emplace_back(newComponent);
		std::string message;
		message = "ID: " + std::to_string(id) + " successfully added a " + typeid(*newComponent).name() + "\n";
		Debug::Log<Entity>(message.c_str());
	}
	else
	{
		std::string message;
		message = "ID: " + std::to_string(id) + " could not add a " + typeid(*newComponent).name() + " to the Entity\n";
		Debug::Warn<Entity>(message.c_str());
		
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

void Entity::do_update(float deltaTime)
{
	transform->update(deltaTime);
	for (unsigned int i = 0; i < components.size(); i++)
	{
		components.at(i)->update(deltaTime);
	}
}

void Entity::do_render(float deltaTime, glm::mat4 view)
{
	transform->render(deltaTime, view);
	for (unsigned int i = 0; i < components.size(); i++)
	{
		components.at(i)->render(deltaTime, view);
	}
}


void Entity::updateBehaviour(float deltaTime)
{
	// do update rate stuff here
	bool shouldUpdate = true;
	halfRateTime += deltaTime;
	quarterRateTIme += deltaTime;
	eighthRateTime += deltaTime;
	frozenTime += deltaTime;

	if(state != UpdateState::frozen && frozenLastFrame)
	{
		frozenLastFrame = false;
		do_update(frozenTime);
	}
	if (state == UpdateState::fullRate)
	{
		do_update(deltaTime);
	}
	else if (state == UpdateState::halfRate)
	{
		if (halfRateCounter == 1)
		{
			shouldUpdate = false;
			halfRateCounter = 0;
		}
		else
		{
			shouldUpdate = true;
			halfRateCounter += 1;
			do_update(halfRateTime);
			halfRateTime = 0.0f;
		}
	}
	else if (state == UpdateState::quarterRate)
	{
		if ((quarterRateCounter + 1) % 4 == 0)
		{
			do_update(quarterRateTIme);
			quarterRateCounter = 0;
			quarterRateTIme = 0.0f;
		}
		else
		{
			quarterRateCounter += 1;
		}
	}
	else if (state == UpdateState::eighthRate)
	{
		if ((eighthRateCounter + 1) % 8 == 0)
		{
			do_update(eighthRateTime);
			eighthRateCounter = 0;
			eighthRateTime = 0.0f;
		}
		else
		{
			eighthRateCounter += 1;
		}
	}
	else if (state == UpdateState::frozen)
	{
		if (!frozenLastFrame)
		{
			frozenTime = 0.0f;
			frozenTime += deltaTime;
		}
		frozenLastFrame = true;
	}
}

void Entity::renderBehaviour(float deltaTime, glm::mat4 view)
{
	if (state == UpdateState::fullRate)
	{
		do_render(deltaTime, view);
	}
	else if (state == UpdateState::halfRate)
	{
		if (halfRateCounter == 1)
		{
			halfRateCounter = 0;
		}
		else
		{
			halfRateCounter += 1;
			do_render(halfRateTime, view);
			halfRateTime = 0.0f;
		}
	}
	else if (state == UpdateState::quarterRate)
	{
		if ((quarterRateCounter + 1) % 4 == 0)
		{
			do_render(quarterRateTIme, view);
			quarterRateCounter = 0;
			quarterRateTIme = 0.0f;
		}
		else
		{
			quarterRateCounter += 1;
		}
	}
	else if (state == UpdateState::eighthRate)
	{
		if ((eighthRateCounter + 1) % 8 == 0)
		{
			do_render(eighthRateTime, view);
			eighthRateCounter = 0;
			eighthRateTime = 0.0f;
		}
		else
		{
			eighthRateCounter += 1;
		}
	}
	
}

void Entity::uiBehaviour(float deltaTime)
{
	for (unsigned int i = 0; i < components.size(); i++)
	{
		components.at(i)->ui(deltaTime);
	}
}

void Entity::AddChild(std::shared_ptr<Entity> e)
{
	children.emplace_back(e);
	std::string message;
	message = "ID: " + std::to_string(id) + " added child with ID: " + std::to_string(e->GetID()) + "\n";
	Debug::Log<Entity>(message.c_str());
}

void Entity::RemoveChild(unsigned _ID)
{
	unsigned int indexToRemove;
	bool canRemove = false;
	for(unsigned int i = 0; i < children.size(); i++)
	{
		if(children.at(i)->GetID() == _ID)
		{
			canRemove = true;
			indexToRemove = i;
		}
	}

	if(canRemove)
	{
		children.erase(children.begin() + indexToRemove);
	}
}

void Entity::ClearChildren()
{
	children.clear();
}

void Entity::RemoveParent()
{
	parent = nullptr;
}

void Entity::SetParent(std::shared_ptr<Entity> newParent)
{
	parent = newParent;
}



std::shared_ptr<Entity> Entity::GetChild(unsigned int index)
{
	if (index <= (children.size() - 1))
	{
		return(std::shared_ptr<Entity>(children.at(index)));
	}

	std::string message;
	message = "ID: " + std::to_string(id) + " could not find child at index: " + std::to_string(index) + "\n";
	Debug::Warn<Entity>(message.c_str());
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

	std::string message;
	message = "ID: " + std::to_string(id) + " could not find child with name: " + name + "\n";
	Debug::Warn<Entity>(message.c_str());
	return nullptr;
}