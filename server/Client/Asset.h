#pragma once

namespace ClientFramework
{
	class Asset
	{
	protected:
		std::string m_sFilename;

	public:
		const std::string& filename() { return m_sFilename; }
		void setFilename(const std::string& sFilename);

	protected:
		virtual void OnSetFilename();

	public:
		virtual void Load();
	};
}
