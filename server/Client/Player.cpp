#include "pch.h"
#include "Player.h"
#include "Key.h"
#include "NetworkManager.h"
#include "Resource.h"
#include "Time.h"

namespace ClientFramework
{
	Player::Player()
		: m_speed(10)
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
		int dx{ 0 }, dy{ 0 };
		if (Key::instance().IsKeyDown(SDLK_w))
			dy -= m_speed;
		if (Key::instance().IsKeyDown(SDLK_s))
			dy += m_speed;
		if (Key::instance().IsKeyDown(SDLK_a))
			dx -= m_speed;
		if (Key::instance().IsKeyDown(SDLK_d))
			dx += m_speed;

		Move(dx * Time::instance().deltaTime(), dy * Time::instance().deltaTime());
	}

	void Player::Render(SDL_Renderer* renderer, const SDL_Point& offset)
	{
		if (m_image)
			SDL_RenderCopyF(renderer, m_image->texture(), NULL, &m_rect);
	}
}