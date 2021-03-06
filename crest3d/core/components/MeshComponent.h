#pragma once

#include "EngineComponent.h"
#include "ShaderComponent.h"
#include "Entity.h"
#include "gfx/Model.h"

class MeshComponent : public EngineComponent
{
public:;
	  MeshComponent(std::shared_ptr<Entity> e, std::shared_ptr<Mesh> newMesh) {
	  	name = "MeshComponent";
	  	attachedEntity = std::shared_ptr<Entity>(e);
	  	mesh = newMesh;
		model = nullptr;
	  	shouldDraw = true;
	  };
	  MeshComponent(std::shared_ptr<Entity> e, std::shared_ptr<Mesh> newMesh, std::shared_ptr<Model> newModel) {
		name = "MeshComponent";
	  	attachedEntity = std::shared_ptr<Entity>(e);
	  	mesh = newMesh;
	  	shouldDraw = true;
	  	model = newModel;
	  };
	  void init() override;
	  void start() override;
	  void earlyUpdate(float deltaTime) override;
	  void update(float deltaTime) override;
	  void render(float deltaTime, glm::mat4 view) override;
	  void ui(float deltaTime) override;
	  void draw(glm::mat4 view, std::shared_ptr<ShaderComponent> _shader);
	  void setShouldDraw(bool newValue) { shouldDraw = newValue; }

	  bool meshIsConvex;
	  // definitely can be changed to be unique
	  std::shared_ptr<Mesh> mesh;
	  std::shared_ptr<Model> model;
	
	  bool shouldDraw;
private:
	int i = 0;

	void draw(glm::mat4 view);

	bool isConvex(std::vector<glm::vec3> points, std::vector<unsigned int> triangles, float threshold);
};
