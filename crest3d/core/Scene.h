#pragma once
#include "Common.h"
#include "Entity.h"

class Scene
{
	Entity* rootEntity = nullptr;
	std::string name;

	Scene(const char* _name);

	void initBehaviour();
	void startBehaviour();
	void earlyUpdateBehaviour();
	void updateBehaviour();
	void uiBehaviour();
};