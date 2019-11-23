#pragma once

#include "Shader.h"

class Material {
public:
	Material() {};
	~Material() {};

	std::vector<std::shared_ptr<Texture>> maps;

	inline void addMap(std::shared_ptr<Texture> t) { maps.emplace_back(t); }
};