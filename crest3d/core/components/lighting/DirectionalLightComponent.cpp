#include "components/lighting/DirectionalLightComponent.h"
#include "Entity.h"
float clampAngle(float input)
{
	float ret;
	if (input > 180.0f)
	{
		ret = -180.0f;
	}
	else if (input < -180.0f)
	{
		ret = 180.0f;
	}
	else
	{
		ret = input;
	}
	return ret;
}


void DirectionalLightComponent::clampDirection()
{
	direction.x = clampAngle(direction.x);
	direction.y = clampAngle(direction.y);
	direction.z = clampAngle(direction.z);
}


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
	// direction = attachedEntity->transform->eulerAngles;
	// clampDirection();
	shader->shader->use();
	shader->shader->setVec3(d + "direction", direction);
	shader->shader->setVec3(d + "ambient", ambient);
	shader->shader->setVec3(d + "diffuse", diffuse);
	shader->shader->setVec3(d + "specular", specular);
}

DirectionalLightComponent::DirectionalLightComponent(std::shared_ptr<Entity> e, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
	name = "DirectionalLightComponent";
	attachedEntity = e;
	this->direction = direction;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
}

DirectionalLightComponent::DirectionalLightComponent(std::shared_ptr<Entity> e)
{
	name = "DirectionalLightComponent";
	attachedEntity = e;
	this->direction = glm::vec3(0.9f);
	this->ambient = glm::vec3(0.3f);
	this->diffuse = glm::vec3(1.0f);
	this->specular = glm::vec3(0.2f);
}

