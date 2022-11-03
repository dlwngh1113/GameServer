#include"stdafx.h"
#include "LoginRequestHandler.h"

void LoginRequestHandler::Init(ClientPeer* peer, BasePacket* packet)
{
	RequestHandler::Init(peer, packet);
}

RequestHandler* LoginRequestHandler::Create()
{
	return new LoginRequestHandler;
}

void LoginRequestHandler::HandleRequest()
{
	LoginRequest* loginPacket = reinterpret_cast<LoginRequest*>(m_packet);
	std::cout << "Client name is " << loginPacket->name << std::endl;

	LoginResponse* res = new LoginResponse();
	res->id = m_peer->GetID();
}