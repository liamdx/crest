#pragma once
#include "Common.h"

class Entity;
class EngineComponent {
public:
	const char* name;
	unsigned int id;
	std::shared_ptr<Entity> attachedEntity = nullptr;

	EngineComponent(const char* componentName = "EngineComponent") { name = componentName; }
	virtual ~EngineComponent() {};
	virtual void init() {};
	virtual void start() {};
	virtual void earlyUpdate(float deltaTime) {};
	virtual void update(float deltaTime) {};
	virtual void fixedUpdate() {};
	virtual void render(float deltaTime, glm::mat4 view) {};
	virtual void ui(float deltaTime) {};
	
	virtual tinyxml2::XMLElement* serialize_component(tinyxml2::XMLDocument* doc) { return doc->NewElement("EngineComponent"); }
	virtual void deserialize_component(tinyxml2::XMLElement* e) {};
				
	inline void SetId(unsigned int newId) { id = newId; }

protected:
	
};

// Virtual static idiom 
//class Foo
//{
//public:
//	Foo();
//
//protected:
//	// Virtual static idiom <-- StaticCallback()
//	virtual bool Callback();
//
//private:
//	// Virtual static idiom --> Callback()
//	static bool StaticCallback(void* pThis)
//	{
//		assert(pThis);
//		return ((Foo*)pThis)->Callback();
//	}
//};