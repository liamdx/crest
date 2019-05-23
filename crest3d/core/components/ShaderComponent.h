#pragma once

#include "EngineComponent.h"
#include "Common.h"
#include "gfx/Shader.h"

class ShaderComponent : public EngineComponent
{
public:
	ShaderComponent(std::shared_ptr<Entity> e, const char* vertexPath = "res/shaders/default.vert", const char* fragPath = "res/shaders/default.frag")
	{
		name = "ShaderComponent"; 
		_vertexPath = vertexPath; 
		_fragPath = fragPath; 
		attachedEntity = std::shared_ptr<Entity>(e);
		view = glm::mat4(1.0);
		projection = glm::mat4(1.0);
	};

	void UpdateShader(glm::mat4 modelMatrix)
	{
		shader->setMat4("model", modelMatrix);
		shader->setMat4("view", view);
		shader->setMat4("projection", projection);
	}

	~ShaderComponent() override {};
	std::shared_ptr<Shader> shader;
	inline void setView(glm::mat4 _view) { view = _view; }
	inline void setProjection(glm::mat4 _projection) { projection = _projection; }

private:
	glm::mat4 view;
	glm::mat4 projection;
	std::string _vertexPath, _fragPath;
};
