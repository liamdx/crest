#include "MeshComponent.h"

void MeshComponent::init() {
	shader = attachedEntity->GetComponent<ShaderComponent>();
}

void MeshComponent::start() {
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
	shader->shader->use();
	shader->UpdateShader(attachedEntity->transform->getModelMatrix());
	mesh.Draw(*shader->shader);
}
