#pragma once

#include "CrestCore.h"

class EngineManager;

class Example {
public:

	virtual ~Example() {};
	
	virtual void initBehaviour() {};
	virtual void startBehaviour() {};
	virtual void earlyUpdateBehaviour(float deltaTime) {};
	virtual void fixedUpdateBehaviour() {};
	virtual void updateBehaviour(float deltaTime) {};
	virtual void renderBehaviour(float deltaTime) {};
	virtual void uiBehaviour(float deltaTime) {};

	std::map<std::string, std::shared_ptr<Entity>> entities;
	std::map<std::string, std::shared_ptr<EngineComponent>> components;

	template<class T>
	std::shared_ptr<T> GetUsableComponent()
	{
		if(std::is_base_of<EngineComponent, T>())
		{
			// iterate through the map of components, i know this shit is ugly.
			for (auto const& [key, val] : components)
			{
				if(typeid(T) == typeid(val.get()))
				{
					return(val);
				}
			}
		}
		else
		{
			std::cout << "The component you are trying to fetch does not derive from EngineComponent\n";
		}
	}
	
	EngineManager* engineManager;
};