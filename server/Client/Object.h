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
		virtual void Render() const = 0;
		virtual void UpdateFrame() = 0;
	};
}
