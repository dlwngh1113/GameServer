#include "pch.h"
#include "Player.h"
#include "Key.h"
#include "NetworkManager.h"
#include "Resource.h"

namespace ClientFramework
{
	Player::Player()
	{
		m_image = (Image*)Resource::instance().GetAsset("player.png");
		if (!m_image)
			std::cerr << "Player image does not exist!\n";

		Teleport(0, 0);
		SetSize(20, 20);
	}

	Player::~Player()
	{
	}

	void Player::UpdateFrame()
	{
		if (Key::instance().IsKeyDown(SDLK_w))
			Move(0, -1);
		if (Key::instance().IsKeyDown(SDLK_a))
			Move(-1, 0);
		if (Key::instance().IsKeyDown(SDLK_s))
			Move(0, 1);
		if (Key::instance().IsKeyDown(SDLK_d))
			Move(1, 0);
	}

	void Player::Render(SDL_Renderer* renderer, const SDL_Point& offset)
	{
		if (m_image)
			SDL_RenderCopyF(renderer, m_image->texture(), NULL, &m_rect);
	}
}