#pragma once

namespace ClientFramework
{
	class Object
	{
	protected:
		SDL_FRect m_rect;

	public:
		Object();

		// Properties
	public:
		virtual const SDL_FPoint pos() const { return SDL_FPoint{ m_rect.x, m_rect.y }; }
		virtual const SDL_FPoint size() const { return SDL_FPoint{ m_rect.w, m_rect.h }; }

		// Member functions
	public:
		virtual void Move(float dx, float dy);
		virtual void Teleport(float x, float y);
		virtual void SetSize(float w, float h);
		virtual void Render(SDL_Renderer* renderer, const SDL_FPoint& offset = { }) = 0;
		virtual void UpdateFrame() = 0;
	};
}
