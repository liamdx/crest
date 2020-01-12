#pragma once
#include "components/EngineComponent.h"

struct LuaScript
{
	LuaScript(const char* filepath);
	std::string script;
	const char* filepath;
	unsigned int scriptID;
	unsigned int priority = 0;
	void reload();

	tinyxml2::XMLElement* serialize(tinyxml2::XMLDocument* doc)
	{
		auto lElement = doc->NewElement("LuaScript");
		lElement->SetAttribute("filepath", filepath);
		return lElement;
	}

};

class LuaComponent : public EngineComponent
{
public:
	LuaComponent(std::shared_ptr<Entity> _attachedEntity);
	LuaComponent(std::shared_ptr<Entity> _attachedEntity, std::shared_ptr<LuaScript> _script);
	~LuaComponent();

	void init() override;
	void start() override;
	void earlyUpdate(float deltaTime) override;
	void update(float deltaTime) override;
	void fixedUpdate() override;
	void render(float deltaTime, glm::mat4 view) override;
	void ui(float deltaTime) override;

	void BindCrestToLua(); // needs to be wayyyy refactored
	std::shared_ptr<LuaScript> script;
	sol::state lua;
	void reload();
	bool shouldRun;

	tinyxml2::XMLElement* serialize_component(tinyxml2::XMLDocument* doc) override;
	void deserialize_component(tinyxml2::XMLElement* e) override;
	
private:
	sol::protected_function init_func;
	sol::protected_function start_func;
	sol::protected_function early_update_func;
	sol::protected_function update_func;
	sol::protected_function fixed_update_func;
	sol::protected_function render_func;
	sol::protected_function ui_func;

	sol::protected_function_result update_result;
	
};