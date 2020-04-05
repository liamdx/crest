#include "AssetManager.h"

AssetManager::AssetManager()
{
	assetCounter = 0;
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
	defaultParticle = loadTextureAsset("res/textures/particle.png");
	defaultParticle->asset->t_Type = TextureType::unknown;
	
}

std::shared_ptr<Asset<Model>> AssetManager::loadModelAsset(const char* path)
{
	std::shared_ptr<Model> m{ new Model(path) } ;
	std::shared_ptr<Asset<Model>> asset = std::make_shared<Asset<Model>>();
	asset->asset = m;
	asset->assetPath = path;
	asset->assetID = getUniqueAssetID();
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
	asset->assetID = getUniqueAssetID();
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
	asset->assetID = getUniqueAssetID();
	textureAssets.emplace_back(asset);
	return asset;
}


void AssetManager::removeModelAsset(unsigned _assetID)
{
	int indexToRemove;
	for (unsigned int i = 0; i < modelAssets.size(); i++)
	{
		if (modelAssets.at(i)->assetID == _assetID)
		{
			indexToRemove = i;
		}
	}
	modelAssets.erase(modelAssets.begin() + indexToRemove);
	removeAssetID(_assetID);
}

void AssetManager::removeAnimatedModelAsset(unsigned _assetID)
{
	int indexToRemove;
	for (unsigned int i = 0; i < animatedModelAssets.size(); i++)
	{
		if (animatedModelAssets.at(i)->assetID == _assetID)
		{
			indexToRemove = i;
		}
	}
	animatedModelAssets.erase(animatedModelAssets.begin() + indexToRemove);
	removeAssetID(_assetID);
}

void AssetManager::removeTextureAsset(unsigned _assetID)
{
	int indexToRemove;
	for (unsigned int i = 0; i < textureAssets.size(); i++)
	{
		if (textureAssets.at(i)->assetID == _assetID)
		{
			indexToRemove = i;
		}
	}

	textureAssets.erase(textureAssets.begin() + indexToRemove);
	removeAssetID(_assetID);
}

unsigned int AssetManager::getUniqueAssetID()
{
	assetCounter += 1;
	assetIDs.emplace_back(assetCounter);
	return assetCounter;
}

void AssetManager::removeAssetID(unsigned assetID)
{
	unsigned int indexToRemove;
	for (int i = 0; i < assetIDs.size(); i++)
	{
		if (assetIDs.at(i) == assetID)
		{
			indexToRemove = i;
		}
	}
	assetIDs.erase(assetIDs.begin() + indexToRemove);
}

std::shared_ptr<Asset<AnimatedModel>> AssetManager::getAnimatedModelAssetID(unsigned id)
{
	for(int i = 0; i < animatedModelAssets.size(); i++)
	{
		if(animatedModelAssets.at(i)->assetID == id)
		{
			return animatedModelAssets.at(i);
		}
	}
}

std::shared_ptr<Asset<Model>> AssetManager::getModelAssetID(unsigned id)
{
	for (int i = 0; i < modelAssets.size(); i++)
	{
		if (modelAssets.at(i)->assetID == id)
		{
			return modelAssets.at(i);
		}
	}
}


std::shared_ptr<Asset<Texture>> AssetManager::getTextureAssetID(unsigned id)
{
	for (int i = 0; i < textureAssets.size(); i++)
	{
		if (textureAssets.at(i)->assetID == id)
		{
			return textureAssets.at(i);
		}
	}
}
