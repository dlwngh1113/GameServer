#pragma once

namespace ClientFramework
{
	class Asset
	{
	protected:
		string m_sFilename;

	public:
		const string& filename() { return m_sFilename; }
		void setFilename(const string& sFilename);

	protected:
		virtual void OnSetFilename();

	public:
		virtual void Load();
	};
}
