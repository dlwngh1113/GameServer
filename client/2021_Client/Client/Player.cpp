#include "pch.h"
#include "Player.h"
#include "Renderer.h"
#include "Singleton.h"

Player::Player()
{
}

Player::Player(int nX, int nY, int nWidth, int nHeight) : MovableObject{ nX, nY, nWidth, nHeight }
{
	SDL_Surface* surface = nullptr;
	surface = SDL_LoadBMP("players.bmp");

	if (!surface)
		std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;

	m_resourcePosition = surface->clip_rect;

	m_texture = SDL_CreateTextureFromSurface(Singleton<Renderer>::GetInstance()->GetRenderer(), surface);

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

void Player::Move(int nDx, int nDy)
{
	m_position.x += nDx;
	m_position.y += nDy;
}
