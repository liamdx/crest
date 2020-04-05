#pragma once
#include "Common.h"
#include "gfx/FrameBuffer.h"
#include "RenderGroup.h"

struct RenderPass {
public: 
	RenderPass(Shader* _shader) { propertyCounter = 0; shader = _shader; pipe = false; }
	~RenderPass() { delete fb; }

	unsigned int id; // location of the render pass frame buffer
	bool pipe;

	void AddProperty(std::string name, unsigned int value);
	void AddProperty(std::string name, float value);
	void AddProperty(std::string name, glm::quat value);
	void AddProperty(std::string name, glm::vec2 value);
	void AddProperty(std::string name, glm::vec3 value);
	void AddProperty(std::string name, glm::mat3 value);
	void AddProperty(std::string name, glm::mat4 value);
	
private:
	std::map<std::string, unsigned int> indexMapping;
	std::map<unsigned int, unsigned int> intProperties;
	std::map<unsigned int, float> floatProperties;
	std::map<unsigned int, glm::quat> quatProperties;
	std::map<unsigned int, glm::vec2> vec2Properties;
	std::map<unsigned int, glm::vec3> vec3Properties;
	std::map<unsigned int, glm::mat3> mat3Properties;
	std::map<unsigned int, glm::mat4> mat4Properties;
	std::vector<unsigned int> activeIndices;

	unsigned int resolution_x, resolution_y;
	unsigned short propertyCounter;
	FrameBuffer* fb;
	Shader* shader;

};

class Pipeline
{
	// must be in sequence. 
	std::vector<RenderPass> passes;
	unsigned int finalImageId; // assumed to be final pass


};