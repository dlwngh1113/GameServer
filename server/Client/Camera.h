#pragma once
#include "Object.h"

namespace ClientFramework
{
	class Camera
	{
	private:
		SDL_FPoint m_offset;
		SDL_FPoint m_pos;
		Object* m_target;

	public:
		Camera();
		virtual ~Camera();

		// Properties
	public:
		const SDL_FPoint& pos() const { return m_pos; }

		// Member functions
	public:
		void SetTarget(Object* target) { m_target = target; }
		void SetOffset(int x, int y);
		void UpdateFrame();
	};
}
