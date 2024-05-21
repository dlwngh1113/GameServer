#include "pch.h"
#include "UIManager.h"

namespace ClientFramework
{
	UIManager UIManager::s_instance;

	void UIManager::AddUI(std::unique_ptr<UIBase> ui, UIType type)
	{
		auto it = m_uiControls.find(type);
		if (it != m_uiControls.end())
			it->second = std::move(ui);
		else
			m_uiControls.insert(std::make_pair(type, std::move(ui)));
	}

	void UIManager::Initialize()
	{
		AddUI(std::make_unique<Label>(), UIType::WndChatting);
	}

	UIBase* UIManager::GetUI(UIType type)
	{
		auto it = m_uiControls.find(type);
		return it != m_uiControls.end() ? it->second.get() : nullptr;
	}
}