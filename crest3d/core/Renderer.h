#pragma once

#include "Common.h"
#include "Scene.h"
#include "Pipeline.h"
#include "RenderGroup.h"
class Renderer
{
public: 
	Renderer();
	~Renderer() {};

	// render every type of drawable in the engine
	void RenderMesh(const std::shared_ptr<Mesh>& m, const std::shared_ptr<Shader>& _shader, const PropertyGroup& props);
	void RenderAnim(const std::shared_ptr<AnimatedModel>& anim, const std::shared_ptr<Shader>& _shader, const PropertyGroup& props);
	void RenderParticleSystem(const std::shared_ptr<ParticleSystem>& ps, const std::shared_ptr<Shader>& _shader, const PropertyGroup& props);
	void RenderPipeline(const std::shared_ptr<RenderGroup>& renderGroup, const std::shared_ptr<Pipeline>& pipeline);
	void RenderPass(const std::shared_ptr<RenderGroup>& renderGroup, const std::shared_ptr<RenderPass>& pipeline);
};
