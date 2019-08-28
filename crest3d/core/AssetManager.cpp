#include "AssetManager.h"

std::shared_ptr<Asset<Model>> AssetManager::loadModelAsset(const char* path)
{
	std::shared_ptr<Model> m = std::make_shared<Model>(path);
	std::shared_ptr<Asset<Model>> asset = std::make_shared<Asset<Model>>();
	asset->asset = m;
	asset->assetPath = path;
	modelAssets.emplace_back(asset);
	return asset;
}

