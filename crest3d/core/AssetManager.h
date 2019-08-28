#pragma once
#include "gfx/Model.h";

template<typename  T>
struct Asset
{
	std::string assetPath;
	std::shared_ptr<T> asset;
};


class AssetManager
{
public:

	AssetManager() {};
	~AssetManager() {};
	
	std::vector<std::shared_ptr<Asset<Model>>> modelAssets;
	std::vector<std::shared_ptr<Asset<Texture>>> textureAssets;

	std::shared_ptr<Asset<Model>> loadModelAsset(const char* path);
};