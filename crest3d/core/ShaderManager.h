#pragma once
#include "components/ShaderComponent.h"
class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager() {};


	std::shared_ptr<ShaderComponent> defaultShader;
	std::shared_ptr<ShaderComponent> defaultAnimShader;
	// further shaders to be added
	// skybox, particles, framebuffer, post processing, shadows etc.
};