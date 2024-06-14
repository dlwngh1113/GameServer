#pragma once
#include "Object.h"

namespace ClientFramework
{
	class Player : public Object
	{
	protected:


	public:
		virtual void UpdateFrame();
		virtual void Render(SDL_Renderer* renderer, const SDL_Point& offset = {}) override;
	};
}
