#pragma once

#include "Common.h"
#include "gfx/Model.h"
#include "gfx/AnimatedModel.h"

class Renderer
{
	Renderer();
	~Renderer() {};

	std::vector<std::shared_ptr<Shader>> shaders;

	void Render(Mesh& mesh);
	void Render(AnimatedModel& anim);
	
};
