#pragma once

#include "Common.h"
#include "Scene.h"
#include "ParticleSystem.h"

class Renderer
{
	Renderer();
	~Renderer() {};

	// render every type of drawable in the engine
	void RenderScene(std::shared_ptr<Scene> scene);
	void RenderMesh(std::shared_ptr<Mesh> m, std::shared_ptr<Shader> _shader);
	void RenderAnim(std::shared_ptr<AnimatedModel> anim, std::shared_ptr<Shader> _shader);
	void RenderParticleSystem(std::shared_ptr<ParticleSystem> anim, std::shared_ptr<Shader> _shader);
	void RenderFrame(unsigned int frameID, std::shared_ptr<Shader> _shader);
	void RenderDirectionalShadowmap(std::vector<std::shared_ptr<Mesh>> meshes, std::vector<std::shared_ptr<AnimatedModel>> anims);
	void RenderCubemapShadowmap(std::vector<std::shared_ptr<Mesh>> meshes, std::vector<std::shared_ptr<AnimatedModel>> anims);

	// will use either a default debug no depth shader or custom
	void DrawLine(glm::vec3 start, glm::vec3 end, glm::vec3 colour);
	void DrawPoint(glm::vec3 position, glm::vec3 colour);
	void DrawLine(glm::vec3 start, glm::vec3 end, glm::vec3 colour, std::shared_ptr<Shader> _shader);
	void DrawPoint(glm::vec3 position, glm::vec3 colour, std::shared_ptr<Shader> _shader);
	
};
