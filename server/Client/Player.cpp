#include "pch.h"
#include "Player.h"
#include "Renderer.h"
#include "PacketSender.h"

Player::Player()
{
	SDL_Surface* surface = nullptr;
	surface = SDL_LoadBMP("players.bmp");

	if (!surface)
		std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;

	m_resourcePosition = surface->clip_rect;
	m_resourcePosition.w -= 32;

	m_texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetRenderer(), surface);

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

void Player::Move(int nX, int nY)
{
	m_position.x = nX * TILE_SIZE;
	m_position.y = nY * TILE_SIZE;
}
