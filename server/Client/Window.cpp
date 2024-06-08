#include "pch.h"
#include "Window.h"

namespace ClientFramework
{
	Window::Window()
	{
		m_parent = this;
		m_rect = { 0, 0, 1280, 720 };
	}

	void Window::Render(SDL_Renderer* renderer)
	{
		OnRender(renderer);
	}
}