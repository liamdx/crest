#pragma once

#include "Common.h"

enum TextureType {
	diffuse,
	normal,
	specular,
	reflection,
	metallic,
	roughness,
	ao,
	unknown
};

struct Texture {
	unsigned int t_Id;
	TextureType t_Type;
	std::string t_Path;
};

class Shader
{
public:
	unsigned int id;

	Shader(const char* vertexPath, const char* fragPath);
	Shader(const char* vertexPath, const char* geometryPath, const char* fragPath);
	void use();
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec3(const std::string& name, glm::vec3 value) const;
	void setMat4(const std::string& name, glm::mat4 value) const;
	void setMat4ID(const unsigned int mat4ID, glm::mat4 value) const;
	void setVec3ID(const unsigned int vec3ID, glm::vec3 value) const;
	void setFloatID(const unsigned int floatID, float value) const;
	void setBoolID(const unsigned int boolID, bool value) const;
	void setIntID(const unsigned int intID, int value) const;
	unsigned int getBoolLocation(const std::string& name);
	unsigned int getIntLocation(const std::string& name);
	unsigned int getFloatLocation(const std::string& name);
	unsigned int getVec3Location(const std::string& name);
	unsigned int getMat4Location(const std::string& name);
	unsigned int getUniformLocation(const std::string& name);

	static std::string textureTypeToShaderName(TextureType t);
	std::map<TextureType, unsigned int> textureIdMappings;

private:
	void fillMappings();
};