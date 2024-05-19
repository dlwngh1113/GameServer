#pragma once
#include "Label.h"
#include "Singleton.h"

namespace ClientFramework
{
	enum class UIType
	{
		WndChatting,
	};

	class UIManager : public Singleton<UIManager>
	{
	private:
		std::unordered_map<UIType, std::unique_ptr<UIBase>> m_uiControls;

	public:
		UIBase* GetUI(UIType type);
	};
}