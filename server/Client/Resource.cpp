#include "pch.h"
#include "Resource.h"
#include "Image.h"

namespace ClientFramework
{
	void Resource::LoadAssets()
	{
		std::unique_ptr<Image> image = std::make_unique<Image>();
		image->setFilename(ResourceDirectory + "player.png");

		AddAsset(move(image));
	}

	void Resource::AddAsset(std::unique_ptr<Asset> asset)
	{
		m_assets.insert(std::make_pair(asset->filename(), move(asset)));
	}

	Asset* Resource::GetAsset(const std::string& sFilename)
	{
		auto iter = m_assets.find(ResourceDirectory + sFilename);
		if (iter != m_assets.end())
			return iter->second.get();

		return nullptr;
	}
}
