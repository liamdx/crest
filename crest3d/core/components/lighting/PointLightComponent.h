#pragma once
#include "components/lighting/LightComponent.h"
#include "components/ShaderComponent.h"

class PointLightComponent : public EngineComponent
{
public:

	PointLightComponent(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float intensity, float distance);
	PointLightComponent();
	void intitalize(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float intensity, float distance);
	void Bind(std::shared_ptr<ShaderComponent> shader, unsigned int index);
	void Bind(std::shared_ptr<ShaderComponent> shader) ;

	inline void setAmbient(glm::vec3 newAmbient) { ambient = newAmbient; }
	inline void setDiffuse(glm::vec3 newDiffuse) { diffuse = newDiffuse; }
	inline void setSpecular(glm::vec3 newSpecular) { specular = newSpecular; }
	inline void setDistance(float newDistance) { distance = newDistance; }
	inline void setIntensity(float newIntensity) { intensity = newIntensity; }

	void update(float deltaTime) override;

private:
	glm::vec3 position;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float intensity;
	float distance;
};