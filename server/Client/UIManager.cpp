#include "pch.h"
#include "UIManager.h"

namespace ClientFramework
{
	UIManager UIManager::s_instance;

	UIBase* UIManager::GetUI(UIType type)
	{
		auto it = m_uiControls.find(type);
		return it != m_uiControls.end() ? it->second.get() : nullptr;
	}
}