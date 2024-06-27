#include "pch.h"
#include "Renderer.h"

namespace ClientFramework
{
	Renderer::Renderer()
		: m_renderer(nullptr)
	{
	}

	bool Renderer::Create(SDL_Window* window)
	{
		m_renderer = SDL_CreateRenderer(window, -1, NULL);

		if (!m_renderer)
			return false;

		return true;
	}

	void Renderer::Release()
	{
		if (m_renderer)
			SDL_DestroyRenderer(m_renderer);
	}
}