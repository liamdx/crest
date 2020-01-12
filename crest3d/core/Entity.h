#pragma once
#include "Common.h"
#include "components/TransformComponent.h"

class EngineManager;

enum UpdateState
{
	fullRate, halfRate, quarterRate, eighthRate, frozen
};

class Entity {
public:

	struct EntityLoadInfo
	{
		std::string _name;
		std::vector<std::string> components;
	};

	std::string name;
	UpdateState state;
	std::vector<std::shared_ptr<EngineComponent>> components;
	std::shared_ptr<Entity> parent;
	std::vector<std::shared_ptr<Entity>> children;
	std::shared_ptr<TransformComponent> transform;

	Entity(const char* entityName, EngineManager* _em, std::shared_ptr<Entity> e);
	~Entity() {}

	inline void SetId(unsigned int newId) { id = newId; }
	inline unsigned int GetID() { return id; }

	void AddComponent(EngineComponent* newComponent);
	// template method only works in .h file without round-about bs
	// any way to keep this in cpp?
	template <class T>
	std::shared_ptr<T> GetComponent()
	{
		for (int i = 0; i < components.size(); i++)
		{
			if (typeid(T) == typeid(*components.at(i)))
			{
				return(std::static_pointer_cast<T>(components.at(i)));
			}
		}
		std::string error = "Could not find component ";
		error += typeid(T).name();
		return nullptr;
	}

	void AddChild(std::shared_ptr<Entity> e);
	void RemoveChild(unsigned int _ID);
	void RemoveParent();
	void ClearChildren();
	void SetParent(std::shared_ptr<Entity> newParent);
	
	std::shared_ptr<Entity> GetChild(unsigned int index);
	std::shared_ptr<Entity> GetChild(const char* name);

	void initBehaviour();
	void startBehaviour();
	void earlyUpdateBehaviour(float deltaTime);
	void fixedUpdateBehaviour();
	void updateBehaviour(float deltaTime);
	void renderBehaviour(float deltaTime, glm::mat4 view);
	void uiBehaviour(float deltaTime);
	
	EngineManager* engineManager;
	int id;
private:
	// for variable update rates;
	void do_update(float deltaTime);
	void do_render(float deltaTime, glm::mat4 view);
	
	uint8_t halfRateCounter, quarterRateCounter, eighthRateCounter;
	bool frozenLastFrame;
	float halfRateTime, quarterRateTIme, eighthRateTime, frozenTime;
	void ConsoleError(std::string error);
	
};
