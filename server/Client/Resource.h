#pragma once
#include "Asset.h"
#include "Singleton.h"

namespace ClientFramework
{
	static const std::string ResourceDirectory{ "../Resources/" };

	class Resource : public Singleton<Resource>
	{
	private:
		std::unordered_map<std::string, std::unique_ptr<Asset>> m_assets;

	public:
		void LoadAssets();
		Asset* GetAsset(const std::string& sFilename);

	private:
		void AddAsset(std::unique_ptr<Asset> asset);
	};
}
