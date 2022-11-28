#include "stdafx.h"
#include "TeleportRequestHandler.h"
#include"CServer.h"

void TeleportRequestHandler::HandleRequest()
{
	TeleportRequest* packet = reinterpret_cast<TeleportRequest*>(m_packet);

	m_user->Teleport(packet->x, packet->y);

	TeleportResponse res;
	res.size = sizeof(TeleportResponse);
	res.type = SC_PACKET_MOVE;

	m_peer->SendPacket(&res);
}

BaseRequestHandler* TeleportRequestHandler::Create()
{
	return new TeleportRequestHandler;
}
