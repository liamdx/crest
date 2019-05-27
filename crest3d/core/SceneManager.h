#pragma once
#include "Scene.h"
#include "components/CameraComponent.h"

class SceneManager
{
	SceneManager() {};

	std::shared_ptr<CameraComponent> camera;
	std::unique_ptr<Scene> scene;
};
