#include "pch.h"
#include "Player.h"
#include "Renderer.h"

Player::Player()
{
}

Player::Player(int nX, int nY, int nWidth, int nHeight) : MovableObject{ nX, nY, nWidth, nHeight }
{
	SDL_Surface* surface = SDL_LoadBMP("players.bmp");
	if (surface == 0)
		std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;

	SDL_CreateTextureFromSurface(Renderer::GetInstance()->GetRenderer(), surface);
}

Player::~Player()
{
}

void Player::Update(float flElapsedTime)
{
}

void Player::Render(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, m_texture, NULL, &m_position);
}

void Player::Move(int nDx, int nDy)
{
	m_position.x += nDx;
	m_position.y += nDy;
}
