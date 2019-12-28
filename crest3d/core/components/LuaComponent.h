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
	// reload all the attached scripts;
	void reload();
	bool shouldRun;
	
private:
	// caching stuff
	// sol::table_proxy<sol::basic_table_core<true, sol::reference>&, std::tuple<const char(&)[7]>>* update_function_proxy;
	//
	sol::protected_function init_func;
	sol::protected_function start_func;
	sol::protected_function early_update_func;
	sol::protected_function update_func;
	sol::protected_function fixed_update_func;
	sol::protected_function render_func;
	sol::protected_function ui_func;
	
};