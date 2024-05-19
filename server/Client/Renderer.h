#pragma once
#include "Singleton.h"

namespace ClientFramework
{
	class Renderer : public Singleton<Renderer>
	{
	private:
		SDL_Renderer* m_renderer;

	public:
		Renderer();

	public:
		SDL_Renderer* renderer() { return m_renderer; }

	public:
		bool Create(SDL_Window* window);
		void Release();
	};
}
