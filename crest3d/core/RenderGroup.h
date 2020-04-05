#pragma once
#include <map>
class Mesh;
class AnimatedModel;
class ParticleSystem;

// render group contains only most basic information needed for drawing
// mvp essentially and the associated object we want to draw
// render pass will load additional properties e.g. shadow map stuff
struct RenderGroup
{
	std::map<Mesh&, glm::mat4&> meshes;
	std::map<AnimatedModel&, glm::mat4&> animatedModels;
	std::map<ParticleSystem&, glm::mat4&> particleSystems;

	glm::mat4 view, proj;

};