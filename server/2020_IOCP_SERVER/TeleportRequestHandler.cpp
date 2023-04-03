#include "stdafx.h"
#include "TeleportRequestHandler.h"
#include "User.h"
#include "Packets.h"
#include "CServer.h"

void TeleportRequestHandler::HandleRequest()
{
	TeleportRequest* packet = reinterpret_cast<TeleportRequest*>(m_packet);

	m_user->SetPosition(packet->x, packet->y);

	// 이벤트 데이터 세팅

	TeleportResponse res;
	res.size = sizeof(TeleportResponse);
	res.type = SC_PACKET_MOVE;

	// 발송

	m_peer->SendPacket(&res);
}

BaseRequestHandler* TeleportRequestHandler::Create()
{
	return new TeleportRequestHandler;
}
