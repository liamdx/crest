#pragma once
#include "components/EngineComponent.h"
#include "gfx/ParticleSystem.h"
#include "components/ShaderComponent.h"

class ParticleSystemComponent : public EngineComponent
{
public:
	ParticleSystemComponent(std::shared_ptr<Entity> e);

	void init() override;
	void start() override;
	void earlyUpdate(float deltaTime) override;
	void update(float deltaTime) override;
	// void render(float deltaTime, glm::mat4 view) override;
	void ui(float deltaTime) override;
	void draw(float deltaTime, glm::mat4 view, std::shared_ptr<ShaderComponent> _shader);

	void reload();

	std::shared_ptr<ParticleSystem> particleSystem;
	std::shared_ptr<Texture> texture;
	std::shared_ptr<CameraComponent> cam;
	void deserialize_component(tinyxml2::XMLElement* e) override;

};
