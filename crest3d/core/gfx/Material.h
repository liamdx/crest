#pragma once

#include "Shader.h"

class Material {
public:
	Material() {};
	~Material() {};

	std::shared_ptr<Shader> shader;
	std::map<std::string, std::shared_ptr<Texture>> maps;

};