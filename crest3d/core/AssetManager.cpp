#include "AssetManager.h"

AssetManager::AssetManager()
{
	defaultDiffuse = loadTextureAsset("res/textures/default_diffuse.png");
	defaultDiffuse->asset->t_Type = TextureType::diffuse;
	defaultNormal = loadTextureAsset("res/textures/default_normal.png");
	defaultNormal->asset->t_Type = TextureType::normal;
	defaultAO = loadTextureAsset("res/textures/default_ao.png");
	defaultAO->asset->t_Type = TextureType::ao;
	defaultMetallic = loadTextureAsset("res/textures/default_metallic.png");
	defaultMetallic->asset->t_Type = TextureType::metallic;
	defaultRoughness = loadTextureAsset("res/textures/default_roughness.png");
	defaultRoughness->asset->t_Type = TextureType::roughness;
}

std::shared_ptr<Asset<Model>> AssetManager::loadModelAsset(const char* path)
{
	std::shared_ptr<Model> m = std::make_shared<Model>(path);
	std::shared_ptr<Asset<Model>> asset = std::make_shared<Asset<Model>>();
	asset->asset = m;
	asset->assetPath = path;
	modelAssets.emplace_back(asset);
	return asset;
}

std::shared_ptr<Asset<AnimatedModel>> AssetManager::loadAnimatedModelAsset(const char* path)
{
	std::shared_ptr<AnimatedModel> m = std::make_shared<AnimatedModel>();
	std::shared_ptr<Asset<AnimatedModel>> asset = std::make_shared<Asset<AnimatedModel>>();
	m->LoadMesh(path);
	asset->asset = m;
	asset->assetPath = path;
	animatedModelAssets.emplace_back(asset);
	return asset;
	
}


std::shared_ptr<Asset<Texture>> AssetManager::loadTextureAsset(const char* path)
{
	std::shared_ptr<Texture> t = std::make_shared<Texture>();
	t->t_Path = path;
	t->t_Id = Model::TextureFromFile(path, "");
	t->t_Type = TextureType::unknown;
	std::shared_ptr<Asset<Texture>> asset = std::make_shared<Asset<Texture>>();
	asset->asset = t;
	asset->assetPath = path;
	return asset;
}

