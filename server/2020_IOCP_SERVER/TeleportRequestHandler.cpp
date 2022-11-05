#include "stdafx.h"
#include "TeleportRequestHandler.h"
#include"CServer.h"

void TeleportRequestHandler::HandleRequest()
{
	User* user = CServer::GetInstance()->GetUser(m_peer->GetID());
	TeleportRequest* packet = reinterpret_cast<TeleportRequest*>(m_packet);

	user->x = packet->x;
	user->y = packet->y;

	TeleportResponse res;
	res.size = sizeof(TeleportResponse);
	res.type = SC_PACKET_MOVE;

	m_peer->SendPacket(reinterpret_cast<unsigned char*>(&res));
}

RequestHandler* TeleportRequestHandler::Create()
{
	return new TeleportRequestHandler;
}
