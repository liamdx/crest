#pragma once
#include "Pipeline.h"

void RenderPass::AddProperty(std::string name, float value)
{
	// if the name isnt already being used
	if (indexMapping.find(name) != indexMapping.end())
	{
		indexMapping[name] = propertyCounter;
		floatProperties[propertyCounter] = value;
		propertyCounter++;
	}
}
void RenderPass::AddProperty(std::string name, unsigned int value)
{
	if (indexMapping.find(name) != indexMapping.end())
	{
		indexMapping[name] = propertyCounter;
		intProperties[propertyCounter] = value;
		propertyCounter++;
	}
}

void RenderPass::AddProperty(std::string name, glm::quat value)
{
	// if the name isnt already being used
	if (indexMapping.find(name) != indexMapping.end())
	{
		indexMapping[name] = propertyCounter;
		quatProperties[propertyCounter] = value;
		propertyCounter++;
	}
}
void RenderPass::AddProperty(std::string name, glm::vec2 value)
{
	if (indexMapping.find(name) != indexMapping.end())
	{
		indexMapping[name] = propertyCounter;
		vec2Properties[propertyCounter] = value;
		propertyCounter++;
	}
}

void RenderPass::AddProperty(std::string name, glm::vec3 value)
{
	// if the name isnt already being used
	if (indexMapping.find(name) != indexMapping.end())
	{
		indexMapping[name] = propertyCounter;
		vec3Properties[propertyCounter] = value;
		propertyCounter++;
	}
}
void RenderPass::AddProperty(std::string name, glm::mat3 value)
{
	if (indexMapping.find(name) != indexMapping.end())
	{
		indexMapping[name] = propertyCounter;
		mat3Properties[propertyCounter] = value;
		propertyCounter++;
	}
}

void RenderPass::AddProperty(std::string name, glm::mat4 value)
{
	if (indexMapping.find(name) != indexMapping.end())
	{
		indexMapping[name] = propertyCounter;
		mat4Properties[propertyCounter] = value;
		propertyCounter++;
	}
}