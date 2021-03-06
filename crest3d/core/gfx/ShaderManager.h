#pragma once
#include "components/ShaderComponent.h"
class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager() {};

	void ReloadDefaultShaders();
	std::shared_ptr<ShaderComponent> defaultShader;
	std::shared_ptr<ShaderComponent> defaultAnimShader;
	std::shared_ptr<ShaderComponent> defaultParticleShader;
	
	// further shaders to be added
	// skybox, particles, framebuffer, post processing, shadows etc.
};