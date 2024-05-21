#include "pch.h"
#include "Player.h"
#include "Key.h"
#include "NetworkManager.h"

namespace ClientFramework
{
	void Player::UpdateFrame()
	{
		if (Key::instance().IsKeyDown(SDLK_w))
		{
			auto body = std::make_shared<Common::ChattingCommandBody>();
			body->id = 0;
			body->message = "Hello World";
			body->type = (short)Command::Chatting;

			NetworkManager::instance().SendPacket(body);
		}
	}

	void Player::Render()
	{
	}
}