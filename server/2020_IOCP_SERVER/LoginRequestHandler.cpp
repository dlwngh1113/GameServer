#include"stdafx.h"
#include "LoginRequestHandler.h"
#include"CServer.h"

BaseRequestHandler* LoginRequestHandler::Create()
{
	return new LoginRequestHandler;
}

void LoginRequestHandler::HandleRequest()
{
	LoginRequest* loginPacket = reinterpret_cast<LoginRequest*>(m_packet);

	LoginResponse* res = new LoginResponse();
	res->size = sizeof(LoginResponse);
	res->type = SC_PACKET_LOGIN_OK;
	res->id = m_peer->GetID();
	res->level = 0;
	res->exp = 0;
	res->hp = 0;
	res->x = 0;
	res->y = 0;
	m_peer->SendPacket(res);
}