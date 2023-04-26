#include "pch.h"
#include "Player.h"

Player::Player()
{
}

Player::Player(int nX, int nY, int nWidth, int nHeight) : MovableObject{ nX, nY, nWidth, nHeight }
{
}

Player::~Player()
{
}

void Player::Update(float flElapsedTime)
{
}

void Player::Render()
{
}

void Player::Move(int nDx, int nDy)
{
	m_position.x += nDx;
	m_position.y += nDy;
}
