#include "pch.h"
#include "UIManager.h"
#include "Label.h"
#include "Window.h"

namespace ClientFramework
{
	UIManager UIManager::s_instance;

	template <typename T>
	void UIManager::AddUI(UIType type)
	{
		auto it = m_uiControls.find(type);
		if (it != m_uiControls.end())
			it->second = std::make_unique<T>();
		else
			m_uiControls.insert(std::make_pair(type, std::make_unique<T>()));
	}

	void UIManager::Initialize()
	{
		AddUI<Window>(UIType::Window);
		AddUI<Label>(UIType::WndChatting);
	}

	UIBase* UIManager::GetUI(UIType type)
	{
		auto it = m_uiControls.find(type);
		return it != m_uiControls.end() ? it->second.get() : nullptr;
	}
}