#pragma once
#include "components/lighting/LightComponent.h"
#include "components/ShaderComponent.h"

class PointLightComponent : public LightComponent
{
public:

	PointLightComponent(std::shared_ptr<Entity> e, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float intensity, float distance);
	PointLightComponent(std::shared_ptr<Entity> e);
	void intitalize(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float intensity, float distance);
	void Bind(std::shared_ptr<ShaderComponent> shader, unsigned int index);
	void Bind(std::shared_ptr<ShaderComponent> shader);

	inline void setAmbient(glm::vec3 newAmbient) { ambient = newAmbient; }
	inline void setDiffuse(glm::vec3 newDiffuse) { diffuse = newDiffuse; }
	inline void setSpecular(glm::vec3 newSpecular) { specular = newSpecular; }
	inline void setDistance(float newDistance) { distance = newDistance; }
	inline void setIntensity(float newIntensity) { intensity = newIntensity; }

	tinyxml2::XMLElement* serialize_component(tinyxml2::XMLDocument* doc) override;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float intensity;
	float distance;

private:
};