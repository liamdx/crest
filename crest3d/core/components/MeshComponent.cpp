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

void MeshComponent::render(float deltaTime)
{
	draw();
}


void MeshComponent::ui(float deltaTime) {

}

void MeshComponent::draw()
{
	shader->shader->use();
	shader->UpdateShader(attachedEntity->transform->getModelMatrix());
	mesh.Draw(*shader->shader);
}
