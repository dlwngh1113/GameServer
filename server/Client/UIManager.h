#pragma once
#include "UIBase.h"
#include "Singleton.h"

namespace ClientFramework
{
	enum class UIType
	{
		Window,
		WndChatting,
	};

	class UIManager : public Singleton<UIManager>
	{
	private:
		std::unordered_map<UIType, std::unique_ptr<UIBase>> m_uiControls;

	private:
		template <typename T>
		void AddUI(UIType type);

	public:
		void Initialize();
		UIBase* GetUI(UIType type);
	};
}