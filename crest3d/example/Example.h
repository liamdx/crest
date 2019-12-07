#pragma once

#include "CrestCore.h"

class EngineManager;

class Example {
public:

	virtual ~Example() {};
	
	virtual void initBehaviour() { inputManager = engineManager->input; };
	virtual void startBehaviour() { };
	virtual void earlyUpdateBehaviour(float deltaTime) {};
	virtual void fixedUpdateBehaviour() {};
	virtual void updateBehaviour(float deltaTime) {};
	virtual void renderBehaviour(float deltaTime) {};
	virtual void uiBehaviour(float deltaTime) {};

	std::map<std::string, std::shared_ptr<Entity>> entities;
	std::map<std::string, std::shared_ptr<EngineComponent>> components;

	template<class T>
	std::shared_ptr<T> GetUsableComponent(const char* path)
	{
		if(std::is_base_of<EngineComponent, T>())
		{
			// iterate through the map of components, i know this shit is ugly.
			std::map<std::string, std::shared_ptr<EngineComponent>>::iterator it;
			
			for (it = components.begin(); it != components.end(); it++)
			{
				if(it->first == path)
				{
					auto item = std::dynamic_pointer_cast<T>(it->second);
					if (item != nullptr)
					{
						return item;
					}
				}
				
			}
		}
		else
		{
			std::cout << "The component you are trying to fetch does not derive from EngineComponent\n";
			return nullptr;
		}
	}

	std::shared_ptr<InputManager> inputManager;
	EngineManager* engineManager;
};