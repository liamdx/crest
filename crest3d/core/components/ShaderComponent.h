#pragma once

#include "EngineComponent.h"
#include "Common.h"
#include "gfx/Shader.h"

class ShaderComponent : public EngineComponent
{
public:
	ShaderComponent(std::shared_ptr<Entity> e, const char* vertexPath = "res/shaders/light.vert", const char* fragPath = "res/shaders/light.frag")
	{
		name = "ShaderComponent";
		_vertexPath = vertexPath;
		_fragPath = fragPath;
		attachedEntity = std::shared_ptr<Entity>(e);
		shader = std::shared_ptr<Shader>(new Shader(vertexPath, fragPath));
		view = glm::mat4(1.0);
		projection = glm::mat4(1.0);

		modelId = shader->getMat4Location("model");
		viewId = shader->getMat4Location("view");
		projectionId = shader->getMat4Location("projection");
		numPointLightsId = shader->getIntLocation("numPointLights");
	};

	inline void UpdateShader(glm::mat4 modelMatrix)
	{
		shader->setMat4ID(modelId, modelMatrix);
		shader->setMat4ID(viewId, view);
		shader->setMat4ID(projectionId, projection);
	}

	inline void UpdateModel(glm::mat4 modelMatrix)
	{
		shader->setMat4ID(modelId, modelMatrix);
	}

	inline void UpdateView(glm::mat4 viewMatrix)
	{
		shader->setMat4ID(viewId, viewMatrix);
	}

	inline void UpdateProjection(glm::mat4 projectionMatrix)
	{
		shader->setMat4ID(projectionId, projectionMatrix);
	}

	inline void SetNumPointLights(unsigned int numPointLights)
	{
		shader->setIntID(numPointLightsId, numPointLights);
	}

	tinyxml2::XMLElement* serialize_component(tinyxml2::XMLDocument* doc) override
	{
		auto scElement = doc->NewElement("ShaderComponent");
		auto shaderElement = shader->serialize(doc);
		scElement->InsertEndChild(shaderElement);
		return scElement;
	}
	
	~ShaderComponent() override {};
	std::shared_ptr<Shader> shader;
	inline void setView(glm::mat4 _view) { view = _view; }
	inline void setProjection(glm::mat4 _projection) { projection = _projection; }
	
	glm::mat4 view;
	glm::mat4 projection;
	std::string _vertexPath, _fragPath;
	unsigned int modelId, projectionId, viewId;
	unsigned int numPointLightsId;
};
