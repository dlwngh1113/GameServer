#include"stdafx.h"
#include "LoginRequestHandler.h"
#include"CServer.h"

void LoginRequestHandler::Init(Peer* peer, BasePacket* packet)
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
	User* user = CServer::GetInstance()->GetUser(m_peer->GetID());

	user->lastMoveTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now()
		.time_since_epoch()).count();
	LoginResponse* res = new LoginResponse();
	res->size = sizeof(LoginResponse);
	res->type = SC_PACKET_LOGIN_OK;
	res->id = m_peer->GetID();
	res->level = 0;
	res->exp = 0;
	res->hp = 0;
	res->x = 0;
	res->y = 0;
	m_peer->SendPacket(reinterpret_cast<unsigned char*>(res));
}