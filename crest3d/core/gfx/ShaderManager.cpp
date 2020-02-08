#include "ShaderManager.h"

ShaderManager::ShaderManager()
{
	defaultShader = std::unique_ptr<ShaderComponent>(new ShaderComponent(NULL, "res/shaders/pbr.vert", "res/shaders/pbr.frag"));
	defaultAnimShader = std::unique_ptr<ShaderComponent>(new ShaderComponent(NULL, "res/shaders/anim.vert", "res/shaders/anim.frag"));
	defaultParticleShader = std::unique_ptr<ShaderComponent>(new ShaderComponent(NULL, "res/shaders/particle.vert", "res/shaders/particle.frag"));
}

void ShaderManager::ReloadDefaultShaders()
{
	defaultShader = std::unique_ptr<ShaderComponent>(new ShaderComponent(NULL, "res/shaders/pbr.vert", "res/shaders/pbr.frag"));
	defaultAnimShader = std::unique_ptr<ShaderComponent>(new ShaderComponent(NULL, "res/shaders/anim.vert", "res/shaders/anim.frag"));
	defaultParticleShader = std::unique_ptr<ShaderComponent>(new ShaderComponent(NULL, "res/shaders/particle.vert", "res/shaders/particle.frag"));
}
