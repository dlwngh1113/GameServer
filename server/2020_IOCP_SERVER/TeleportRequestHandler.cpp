#include "stdafx.h"
#include "TeleportRequestHandler.h"
#include"CServer.h"

void TeleportRequestHandler::HandleRequest()
{
	User* user = CServer::GetInstance()->GetUser(m_peer->GetID());
	TeleportRequest* packet = reinterpret_cast<TeleportRequest*>(m_packet);

	user->x = packet->x;
	user->y = packet->y;

	TeleportResponse* res = new TeleportResponse();
	res->size = sizeof(TeleportResponse);
	res->type = SC_PACKET_MOVE;

	m_peer->SendPacket(res);
}

BaseRequestHandler* TeleportRequestHandler::Create()
{
	return new TeleportRequestHandler;
}
