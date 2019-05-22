#include "MeshComponent.h"
#include "Common.h"
#include "ShaderComponent.h"

void MeshComponent::init() {
	ShaderComponent* sc = (ShaderComponent*)attachedEntity->GetComponent("ShaderComponent");
	if (sc != nullptr)
		shader = &sc->shader;
	else
		shader = nullptr;
	
}

void MeshComponent::start() {
	updateModelMatrix();
}

void MeshComponent::earlyUpdate() 
{
	updateModelMatrix();
}

void MeshComponent::update() {

}

void MeshComponent::ui() {

}

void MeshComponent::updateModelMatrix()
{
	model = glm::translate(model, attachedEntity->transform->position);
	model = glm::scale(model, attachedEntity->transform->scale);
	glm::vec3 currentEulerAngles = attachedEntity->transform->eulerAngles;
	model = glm::rotate(model, currentEulerAngles.x, glm::vec3(1.0, 0.0, 0.0));
	model = glm::rotate(model, currentEulerAngles.y, glm::vec3(0.0, 1.0, 0.0));
	model = glm::rotate(model, currentEulerAngles.z, glm::vec3(0.0, 0.0, 1.0));
}