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
	void earlyUpdate(float deltaTime) override;
	void update(float deltaTime) override;
	void render(float deltaTime, glm::mat4 view) override;
	void ui(float deltaTime) override;


private:
	void draw(glm::mat4 view);
	Mesh mesh;
	std::shared_ptr<ShaderComponent> shader;

};