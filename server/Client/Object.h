#pragma once

namespace ClientFramework
{
	class Object
	{
	protected:
		SDL_FRect m_rect;

	public:
		Object();

	public:
		virtual void Move(int dx, int dy);
		virtual void Teleport(int x, int y);
		virtual void Render(SDL_Renderer* renderer, const SDL_Point& offset = { }) = 0;
		virtual void UpdateFrame() = 0;
	};
}
