#pragma once
#include "Asset.h"

namespace ClientFramework
{
	static const std::string ResourceDirectory{ "../Resources/" };

	class Resource
	{
	private:
		std::unordered_map<std::string, std::unique_ptr<Asset>> m_assets;

	public:
		void LoadAssets();
		Asset* GetAsset(const std::string& sFilename);

	private:
		void AddAsset(std::unique_ptr<Asset> asset);

		// Static Member Variables
	private:
		static Resource s_instance;

		// Static Member Functions
	public:
		static Resource& instance() { return s_instance; }
	};
}
