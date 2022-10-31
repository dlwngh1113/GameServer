#include"stdafx.h"
#include "LoginRequestHandler.h"

void LoginRequestHandler::HandleRequest(BasePacket* packet)
{
	LoginPacket* loginPacket = reinterpret_cast<LoginPacket*>(packet);
	std::cout << "Client name is " << loginPacket->name << std::endl;
}