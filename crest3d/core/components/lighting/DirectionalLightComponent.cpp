#include "components/lighting/DirectionalLightComponent.h"

void DirectionalLightComponent::initialize(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
	this->direction = direction;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
}

void DirectionalLightComponent::Bind(std::shared_ptr<ShaderComponent> shader)
{
	std::string d = "dirLight.";

	shader->shader->use();
	shader->shader->setVec3(d + "direction", direction);
	shader->shader->setVec3(d + "ambient", ambient);
	shader->shader->setVec3(d + "diffuse", diffuse);
	shader->shader->setVec3(d + "specular", specular);
}

DirectionalLightComponent::DirectionalLightComponent(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
	name = "DirectionalLightComponent";
	this->direction = direction;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
}

DirectionalLightComponent::DirectionalLightComponent()
{
	name = "DirectionalLightComponent";
	this->direction = glm::vec3(-0.5f);
	this->ambient = glm::vec3(0.0f);
	this->diffuse = glm::vec3(0.7f);
	this->specular = glm::vec3(0.1f);
}