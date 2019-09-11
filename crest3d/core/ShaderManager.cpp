#include "ShaderManager.h"

ShaderManager::ShaderManager()
{
	defaultShader = std::shared_ptr<ShaderComponent>(new ShaderComponent(NULL, "res/shaders/pbr.vert", "res/shaders/pbr.frag"));
	defaultAnimShader = std::shared_ptr<ShaderComponent>(new ShaderComponent(NULL, "res/shaders/anim.vert", "res/shaders/anim.frag"));
}
