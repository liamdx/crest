#pragma once

#include "components/lighting/LightComponent.h"
#include "components/ShaderComponent.h"

class DirectionalLightComponent : public LightComponent
{
public:
	void initialize(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
	void Bind(std::shared_ptr<ShaderComponent> shader);

	DirectionalLightComponent(std::shared_ptr<Entity> e, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
	DirectionalLightComponent(std::shared_ptr<Entity> e);
	void clampDirection();

	tinyxml2::XMLElement* serialize_component(tinyxml2::XMLDocument* doc) override;

	glm::vec3 direction;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};