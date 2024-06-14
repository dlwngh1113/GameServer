#include "pch.h"
#include "Player.h"
#include "Key.h"
#include "NetworkManager.h"

namespace ClientFramework
{
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
	}
}