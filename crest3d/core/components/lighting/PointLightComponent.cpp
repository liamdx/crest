#include "components/lighting/PointLightComponent.h"
#include "Entity.h"
#include "serialization/Serializer.hpp"

PointLightComponent::PointLightComponent(std::shared_ptr<Entity> e, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float intensity, float distance)
{
	this->attachedEntity = e;
	this->name = "PointLightComponent";
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->intensity = intensity;
	this->distance = distance;
}

PointLightComponent::PointLightComponent(std::shared_ptr<Entity> e)
{
	this->attachedEntity = e;
	this->name = "PointLightComponent";
	this->ambient = glm::vec3(0.0f);
	this->diffuse = glm::vec3(1.0f);
	this->specular = glm::vec3(0.0f);
	this->intensity = 1.0f;
	this->distance = 5.0f;
}

void PointLightComponent::intitalize(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float intensity, float distance)
{
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->intensity = intensity;
	this->distance = distance;
}

void PointLightComponent::Bind(std::shared_ptr<ShaderComponent> shader, unsigned int index)
{
	std::stringstream ss;
	ss << "pointLights[" << index << "].";
	std::string s = ss.str();

	shader->shader->setVec3(s + "position", attachedEntity->transform->position);
	shader->shader->setVec3(s + "ambient", ambient);
	shader->shader->setVec3(s + "diffuse", diffuse);
	shader->shader->setVec3(s + "specular", specular);
	shader->shader->setFloat(s + "intensity", intensity);
	shader->shader->setFloat(s + "distance", distance);
}

void PointLightComponent::Bind(std::shared_ptr<ShaderComponent> shader)
{
	std::stringstream ss;
	ss << "debugLight.";
	std::string s = ss.str();

	shader->shader->setVec3(s + "position", attachedEntity->transform->position);
	shader->shader->setVec3(s + "ambient", ambient);
	shader->shader->setVec3(s + "diffuse", diffuse);
	shader->shader->setVec3(s + "specular", specular);
	shader->shader->setFloat(s + "intensity", intensity);
	shader->shader->setFloat(s + "distance", distance);
}

tinyxml2::XMLElement* PointLightComponent::serialize_component(tinyxml2::XMLDocument* doc)
{
	auto plElement = doc->NewElement("PointLightComponent");
	plElement->LinkEndChild(Serializer::SerializeVec3(ambient, "ambient", doc));
	plElement->LinkEndChild(Serializer::SerializeVec3(diffuse, "diffuse", doc));
	plElement->LinkEndChild(Serializer::SerializeVec3(specular, "specular", doc));
	plElement->LinkEndChild(Serializer::SerializeFloat(intensity, "intensity", doc));
	plElement->LinkEndChild(Serializer::SerializeFloat(distance, "distance", doc));
	return plElement;
}
