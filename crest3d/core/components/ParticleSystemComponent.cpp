#include "components/ParticleSystemComponent.h"
#include "EngineManager.h"

ParticleSystemComponent::ParticleSystemComponent(std::shared_ptr<Entity> e)
{
	name = "ParticleSystemComponent";
	attachedEntity = e;
	particleSystem = std::make_shared<ParticleSystem>();
}


void ParticleSystemComponent::init()
{
	particleSystem->init();
	particleSystem->texture = attachedEntity->engineManager->assetManager->defaultParticle->asset->t_Id;
}


void ParticleSystemComponent::start()
{
	cam = attachedEntity->engineManager->scene->sceneCamera;
	texture = attachedEntity->engineManager->assetManager->defaultParticle->asset;
}

void ParticleSystemComponent::earlyUpdate(float deltaTime)
{
	
}

void ParticleSystemComponent::update(float deltaTime)
{
	particleSystem->position = attachedEntity->transform->position;
	particleSystem->scale = attachedEntity->transform->scale;
	particleSystem->update(deltaTime, cam);
}

void ParticleSystemComponent::ui(float deltaTime)
{
	
}

void ParticleSystemComponent::deserialize_component(tinyxml2::XMLElement* e)
{
	
}


void ParticleSystemComponent::reload()
{
	
}

void ParticleSystemComponent::draw(float deltaTime, glm::mat4 view, std::shared_ptr<ShaderComponent> _shader)
{
	particleSystem->render(deltaTime, cam, _shader->shader);
}



