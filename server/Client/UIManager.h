#pragma once
#include "Label.h"

namespace ClientFramework
{
	enum class UIType
	{
		WndChatting,
	};

	class UIManager
	{
	private:
		std::unordered_map<UIType, std::unique_ptr<UIBase>> m_uiControls;

	public:
		UIBase* GetUI(UIType type);

		// Static member variables
	private:
		static UIManager s_instance;

		// Static member functions
	public:
		static UIManager& instance() { return s_instance; }
	};
}