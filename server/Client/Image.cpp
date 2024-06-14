#include "pch.h"
#include "Image.h"
#include "Resource.h"
#include "Renderer.h"

namespace ClientFramework
{
	void Image::OnSetFilename()
	{
		SDL_Surface* pHellowBMP = IMG_Load(m_sFilename.c_str());
		if (!pHellowBMP)
		{
			std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
			return;
		}

		m_texture = SDL_CreateTextureFromSurface(Renderer::instance().renderer(), pHellowBMP);

		SDL_FreeSurface(pHellowBMP);
	}

	void Image::Load()
	{
	}
}