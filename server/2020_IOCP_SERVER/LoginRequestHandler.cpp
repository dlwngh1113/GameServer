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
	res->size = sizeof(*res);
	res->type = SC_PACKET_LOGIN_OK;
	res->id = m_peer->GetID();
	res->level = 0;
	res->exp = 0;
	res->hp = 0;
	res->x = 0;
	res->y = 0;
	m_peer->SendPacket(reinterpret_cast<unsigned char*>(res));
}