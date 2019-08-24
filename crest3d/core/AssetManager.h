#pragma once
#include "gfx/Model.h";


static class AssetManager
{
public:

	template<typename  T>
	struct Asset
	{
		std::string assetPath;
		std::shared_ptr<T> asset;
	};
	
	~AssetManager() = default;

	std::vector<Asset<Model>> modelAssets;


	

private:
	
};