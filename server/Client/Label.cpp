#include "pch.h"
#include "Label.h"
#include "Renderer.h"

namespace ClientFramework
{
	Label::Label()
		: m_surface(nullptr)
		, m_font(nullptr)
		, m_texture(nullptr)
		, m_color()
	{
		m_font = TTF_OpenFont("./Wavve.ttf", 16);
		if (m_font == nullptr)
			std::cerr << "Font didn't load\n";

		m_surface = TTF_RenderText_Blended(m_font, "Test String", m_color);
	}

	Label::~Label()
	{
		if (m_surface)
		{
			SDL_FreeSurface(m_surface);
			m_surface = nullptr;
		}

		if (m_font)
		{
			TTF_CloseFont(m_font);
			m_font = nullptr;
		}

		if (m_texture)
		{
			SDL_DestroyTexture(m_texture);
			m_texture = nullptr;
		}
	}
	
	void Label::Initialize()
	{
		m_texture = SDL_CreateTextureFromSurface(Renderer::instance().renderer(), m_surface);
	}

	void Label::Render(SDL_Renderer* renderer)
	{
		SDL_RenderCopy(renderer, m_texture, NULL, NULL);
	}

	void Label::SetText(const std::string& text)
	{
		SDL_Surface* prevSurface = m_surface;
		m_surface = TTF_RenderText_Blended(m_font, text.c_str(), m_color);
		
		SDL_Texture* prevTexture = m_texture;
		m_texture = SDL_CreateTextureFromSurface(Renderer::instance().renderer(), m_surface);

		SDL_FreeSurface(prevSurface);
		SDL_DestroyTexture(prevTexture);
	}
}