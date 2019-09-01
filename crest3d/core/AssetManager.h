#pragma once

#include "gfx/AnimatedModel.h"
template<typename  T>
struct Asset
{
	std::string assetPath;
	std::shared_ptr<T> asset;
};


class AssetManager
{
public:

	AssetManager();
	~AssetManager() {};
	
	std::vector<std::shared_ptr<Asset<Model>>> modelAssets;
	std::vector<std::shared_ptr<Asset<AnimatedModel>>> animatedModelAssets;
	std::vector<std::shared_ptr<Asset<Texture>>> textureAssets;

	std::shared_ptr<Asset<Texture>> defaultDiffuse;
	std::shared_ptr<Asset<Texture>> defaultNormal;
	std::shared_ptr<Asset<Texture>> defaultAO;
	std::shared_ptr<Asset<Texture>> defaultMetallic;
	std::shared_ptr<Asset<Texture>> defaultRoughness;

	std::shared_ptr<Asset<Model>> loadModelAsset(const char* path);
	std::shared_ptr<Asset<AnimatedModel>> loadAnimatedModelAsset(const char* path);
	std::shared_ptr<Asset<Texture>> loadTextureAsset(const char* path);
};