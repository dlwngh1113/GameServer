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
		virtual void Move(float dx, float dy);
		virtual void Teleport(float x, float y);
		virtual void SetSize(float w, float h);
		virtual void Render(SDL_Renderer* renderer, const SDL_Point& offset = { }) = 0;
		virtual void UpdateFrame() = 0;
	};
}
