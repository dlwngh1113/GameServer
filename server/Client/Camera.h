#pragma once

namespace ClientFramework
{
	class Camera
	{
	private:
		SDL_Point m_pos;

	public:
		virtual ~Camera();
		void SetPos(const SDL_Point& pos) { m_pos = pos; }
		void Render(SDL_Renderer* renderer);
	};
}
