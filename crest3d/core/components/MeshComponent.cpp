#include "MeshComponent.h"

void MeshComponent::init() {
	shader = attachedEntity->GetComponent<ShaderComponent>();
}

void MeshComponent::start() {
}

void MeshComponent::earlyUpdate(float deltaTime)
{
	
}

void MeshComponent::update(float deltaTime) {

}

void MeshComponent::render(float deltaTime, glm::mat4 view)
{
	draw(view);
}


void MeshComponent::ui(float deltaTime) {

}

void MeshComponent::draw(glm::mat4 view)
{
	shader->shader->use();
	shader->setView(view);
	shader->UpdateShader(attachedEntity->transform->getModelMatrix());
	mesh.Draw(*shader->shader);
}
