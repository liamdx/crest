#pragma once

#include "EngineComponent.h"
#include "gfx/Mesh.h"

#include "Entity.h"

class MeshComponent : public EngineComponent
{
public: 
	MeshComponent(Mesh newMesh) : mesh(newMesh) { name = "MeshComponent"; };

	void init() override;
	void start() override;
	void earlyUpdate() override;
	void update() override;
	void ui() override;

	Entity* attachedEntity;

private:
	void updateModelMatrix();
	glm::mat4 model = glm::mat4(1.0);
	Mesh mesh;
	Shader* shader;

};