#pragma once
#include "Common.h"

class LuaManager
{
public:

	LuaManager() {};
	~LuaManager() {};

	sol::state global_lua_state;
	
	
};