#include "pch.h"
#include "Resource.h"
#include "Image.h"

namespace ClientFramework
{
	Resource Resource::s_instance;

	void Resource::LoadAssets()
	{
		unique_ptr<Image> image = make_unique<Image>();
		image->setFilename(ResourceDirectory + "test.bmp");

		AddAsset(move(image));
	}

	void Resource::AddAsset(unique_ptr<Asset> asset)
	{
		m_assets.insert(make_pair(asset->filename(), move(asset)));
	}

	Asset* Resource::GetAsset(const string& sFilename)
	{
		auto iter = m_assets.find(sFilename);
		if (iter != m_assets.end())
			return iter->second.get();

		return nullptr;
	}
}
