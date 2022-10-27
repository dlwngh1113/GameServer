#include "User.h"

User::User() : ClientPeer()
{
}

User::~User()
{
}

void User::OnDisconnect()
{
}

void User::ProcessPacket(BasePacket* packet)
{
	switch (packet->type)
	{
	case CS_LOGIN:

		break;
	default:
		break;
	}
}
