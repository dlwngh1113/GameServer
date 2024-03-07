#include "pch.h"
#include "Player.h"
#include "PacketSender.h"
#include "Framework.h"

Player::Player()
{
	SDL_Surface* surface = nullptr;
	surface = SDL_LoadBMP("players.bmp");

	if (!surface)
	{
		std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
		return;
	}

	m_resourcePosition = surface->clip_rect;
	m_resourcePosition.w -= 32;

	m_texture = SDL_CreateTextureFromSurface(Framework::GetInstance().renderer(), surface);

	SDL_FreeSurface(surface);
}

Player::~Player()
{
	SDL_DestroyTexture(m_texture);
}

void Player::Update(float flElapsedTime)
{
}

void Player::Render(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, m_texture, &m_resourcePosition, &m_position);
}
