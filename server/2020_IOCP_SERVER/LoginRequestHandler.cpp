#include"stdafx.h"
#include "LoginRequestHandler.h"

void LoginRequestHandler::Init(ClientPeer* peer, BasePacket* packet)
{
	IRequestHandler::Init(peer, packet);
}

void LoginRequestHandler::Handle()
{
	LoginPacket* loginPacket = reinterpret_cast<LoginPacket*>(m_packet);
	std::cout << "Client name is " << loginPacket->name << std::endl;
}