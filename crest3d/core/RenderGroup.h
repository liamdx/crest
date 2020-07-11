#pragma once
#include "Common.h"
class Mesh;
class AnimatedModel;
class ParticleSystem;

struct PropertyGroup
{
public:
	void AddProperty(std::string name, unsigned int value);
	void AddProperty(std::string name, float value);
	void AddProperty(std::string name, glm::quat value);
	void AddProperty(std::string name, glm::vec2 value);
	void AddProperty(std::string name, glm::vec3 value);
	void AddProperty(std::string name, glm::mat3 value);
	void AddProperty(std::string name, glm::mat4 value);

	template <typename T>
	T GetProperty(std::string name)
	{
		// property exists in index mapping
		if (indexMapping.find(name) != indexMapping.end())
		{
			unsigned int index = indexMapping.at(name);

			if (intProperties.find(index) != intProperties.end()) { return intProperties.at(index); }
			if (floatProperties.find(index) != floatProperties.end()) { return floatProperties.at(index); }
			if (quatProperties.find(index) != quatProperties.end()) { return quatProperties.at(index); }
			if (vec2Properties.find(index) != vec2Properties.end()) { return vec2Properties.at(index); }
			if (vec3Properties.find(index) != vec3Properties.end()) { return vec3Properties.at(index); }
			if (mat3Properties.find(index) != mat3Properties.end()) { return mat3Properties.at(index); }
			if (mat4Properties.find(index) != mat4Properties.end()) { return mat4Properties.at(index); }
		}

		return NULL;
	}

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
	unsigned short propertyCounter = 0;
};

struct RenderGroup
{
	std::map<std::shared_ptr<Mesh>, PropertyGroup> meshes;
	std::map<std::shared_ptr<AnimatedModel>, PropertyGroup> animatedModels;
	std::map<std::shared_ptr<ParticleSystem>, PropertyGroup> particleSystems;

	glm::mat4 view, proj;

};