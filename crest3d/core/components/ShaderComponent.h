#pragma once

#include "EngineComponent.h"
#include "Common.h"
#include "gfx/Shader.h"

class ShaderComponent : public EngineComponent
{
public:
	ShaderComponent(const char* vertexPath, const char* fragPath) : shader(vertexPath, fragPath) 
	{ name = "ShaderComponent"; _vertexPath = vertexPath; _fragPath = fragPath; };


	~ShaderComponent() override {};

	//void init() override;
	//void start() override;
	//void earlyUpdate() override;
	//void update() override;
	//void ui() override;

	Shader shader;

private:
	std::string _vertexPath, _fragPath;
};