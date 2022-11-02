#include"stdafx.h"
#include "LoginRequestHandler.h"

void LoginRequestHandler::Init(ClientPeer* peer, BasePacket* packet)
{
	IRequestHandler::Init(peer, packet);
}

void LoginRequestHandler::Handle()
{
	LoginRequest* loginPacket = reinterpret_cast<LoginRequest*>(m_packet);
	std::cout << "Client name is " << loginPacket->name << std::endl;

	LoginResponse* res = new LoginResponse();
	res->id = m_peer->GetID();
}