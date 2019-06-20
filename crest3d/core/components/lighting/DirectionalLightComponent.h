#pragma once

#include "components/lighting/LightComponent.h"
#include "components/ShaderComponent.h"

class DirectionalLightComponent : public EngineComponent
{
public:
	void initialize(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
	void Bind(std::shared_ptr<ShaderComponent> shader);

	DirectionalLightComponent(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
	DirectionalLightComponent();


	glm::vec3 direction;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	
};