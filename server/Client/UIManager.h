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

	private:
		void AddUI(std::unique_ptr<UIBase> ui, UIType type);

	public:
		void Initialize();
		UIBase* GetUI(UIType type);
	};
}