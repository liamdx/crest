#pragma once
#include "Scene.h"

class SceneManager
{
	SceneManager() {};

	std::unique_ptr<Scene> scene;
};