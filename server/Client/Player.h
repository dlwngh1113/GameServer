#pragma once
#include "Object.h"
#include "Image.h"

namespace ClientFramework
{
	class Player : public Object
	{
	protected:
		Image* m_image;

	public:
		Player();
		virtual ~Player();

	public:
		virtual void UpdateFrame();
		virtual void Render(SDL_Renderer* renderer, const SDL_Point& offset = {}) override;
	};
}
