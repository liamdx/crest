#pragma once

#include "EngineComponent.h"
#include "ShaderComponent.h"
#include "gfx/Mesh.h"
#include "Entity.h"

class MeshComponent : public EngineComponent
{
public: 
	MeshComponent(std::shared_ptr<Entity> e, Mesh newMesh) : mesh(newMesh) { name = "MeshComponent"; attachedEntity = std::shared_ptr<Entity>(e); };

	void init() override;
	void start() override;
	void earlyUpdate() override;
	void update() override;
	void ui() override;


private:
	void draw();
	void updateModelMatrix();
	glm::mat4 model = glm::mat4(1.0);
	Mesh mesh;
	std::shared_ptr<ShaderComponent> shader;

};