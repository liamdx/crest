#pragma once

#include "gfx/AnimatedModel.h"
#include "components/AudioComponent.h"

template<typename  T>
struct Asset
{
	std::string assetPath;
	unsigned int assetID;
	std::shared_ptr<T> asset;
};

class AssetManager
{
public:

	AssetManager();
	~AssetManager() {};

	std::shared_ptr<Asset<Texture>> defaultDiffuse;
	std::shared_ptr<Asset<Texture>> defaultNormal;
	std::shared_ptr<Asset<Texture>> defaultAO;
	std::shared_ptr<Asset<Texture>> defaultMetallic;
	std::shared_ptr<Asset<Texture>> defaultRoughness;

	std::shared_ptr<Asset<Model>> loadModelAsset(const char* path);
	std::shared_ptr<Asset<AnimatedModel>> loadAnimatedModelAsset(const char* path);
	std::shared_ptr<Asset<Texture>> loadTextureAsset(const char* path);
	std::shared_ptr<Asset<AudioFile>> loadAudioAsset(const char* path);


	std::shared_ptr<Asset<Model>> getModelAssetID(unsigned int id);
	std::shared_ptr<Asset<AnimatedModel>> getAnimatedModelAssetID(unsigned int id);
	std::shared_ptr<Asset<Texture>> getTextureAssetID(unsigned int id);
	std::shared_ptr<Asset<AudioFile>> getAudioAssetID(unsigned int id);

	

	void removeModelAsset(unsigned int _assetID);
	void removeAnimatedModelAsset(unsigned int _assetID);
	void removeTextureAsset(unsigned int _assetID);
	void removeAudioAsset(unsigned int _assetID);

	unsigned int getUniqueAssetID();

private:

	void removeAssetID(unsigned int assetID);

	std::vector<std::shared_ptr<Asset<Model>>> modelAssets;
	std::vector<std::shared_ptr<Asset<AnimatedModel>>> animatedModelAssets;
	std::vector<std::shared_ptr<Asset<Texture>>> textureAssets;
	std::vector<std::shared_ptr<Asset<AudioFile>>> audioAssets;
	std::vector<unsigned int> assetIDs;
	unsigned int assetCounter;
};