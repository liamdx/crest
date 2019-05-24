#include "MeshComponent.h"

void MeshComponent::init() {
	shader = attachedEntity->GetComponent<ShaderComponent>();
	
}

void MeshComponent::start() {
	updateModelMatrix();
}

void MeshComponent::earlyUpdate() 
{
	
}

void MeshComponent::update() {
	draw();
}

void MeshComponent::ui() {

}

void MeshComponent::draw()
{
	updateModelMatrix();
	shader->UpdateShader(model);
	mesh.Draw(*shader->shader);
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