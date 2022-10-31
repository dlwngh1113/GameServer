#include"stdafx.h"
#include "User.h"

User::User(BaseRequestHandlerFactory* instance) : ClientPeer(instance)
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

}
