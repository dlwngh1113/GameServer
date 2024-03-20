#pragma once
#include "Asset.h"

namespace ClientFramework
{
	static const string ResourceDirectory{ "../Resources/" };

	class Resource
	{
	private:
		unordered_map<string, unique_ptr<Asset>> m_assets;

	public:
		void LoadAssets();
		Asset* GetAsset(const string& sFilename);

	private:
		void AddAsset(unique_ptr<Asset> asset);

		// Static Member Variables
	private:
		static Resource s_instance;

		// Static Member Functions
	public:
		static Resource& instance() { return s_instance; }
	};
}
