#pragma once
#include "UIBase.h"

namespace ClientFramework
{
	class Window : public UIBase
	{
	public:
		Window();

	public:
		virtual void Render(SDL_Renderer* renderer) override;
	};
}
