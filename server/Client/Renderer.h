#pragma once

namespace ClientFramework
{
	class Renderer
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

		// Static Member Variables
	private:
		static Renderer s_instance;

		// Static Member Functions
	public:
		static Renderer& instance() { return s_instance; }
	};
}
