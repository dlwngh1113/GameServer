#include "pch.h"
#include "Asset.h"

namespace ClientFramework
{
	void Asset::setFilename(const std::string& sFilename)
	{
		m_sFilename = sFilename;

		OnSetFilename();
	}

	void Asset::OnSetFilename()
	{
	}

	void Asset::Load()
	{
	}
}
