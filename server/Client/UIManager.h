#pragma once
#include "Label.h"

namespace ClientFramework
{
	enum class UIType
	{

	};

	class UIManager
	{
	private:
		std::unordered_map<UIType, std::unique_ptr<UIBase>> m_uiControls;

	public:
		UIBase* GetUI(UIType type);
	};
}