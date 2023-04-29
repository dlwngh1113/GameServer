#include "stdafx.h"
#include "TeleportRequestHandler.h"
#include "User.h"
#include "Packets.h"
#include "CServer.h"

void TeleportRequestHandler::HandleInGame()
{
	ClientCommon::TeleportRequest* packet = reinterpret_cast<ClientCommon::TeleportRequest*>(m_packet);

	m_user->SetPosition(packet->x, packet->y);

	// 이벤트 데이터 세팅

	ClientCommon::TeleportResponse res;
	res.header.size = sizeof(ClientCommon::TeleportResponse);
	res.header.type = static_cast<short>(ServerCommand::UserMove);

	// 발송

	m_peer->SendPacket(&res);
}

BaseRequestHandler* TeleportRequestHandler::Create()
{
	return new TeleportRequestHandler;
}
