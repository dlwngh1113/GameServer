#include "stdafx.h"
#include "TeleportRequestHandler.h"
#include "User.h"
#include "Packets.h"
#include "CServer.h"

void TeleportRequestHandler::HandleInGame()
{
	ClientCommon::TeleportRequest* packet = reinterpret_cast<ClientCommon::TeleportRequest*>(m_packet);

	m_user->SetPosition(packet->x, packet->y);

	// �̺�Ʈ ������ ����

	ClientCommon::TeleportResponse res;
	res.header.size = sizeof(ClientCommon::TeleportResponse);
	res.header.type = static_cast<short>(ServerCommand::UserMove);

	// �߼�

	m_peer->SendPacket(&res);
}

BaseRequestHandler* TeleportRequestHandler::Create()
{
	return new TeleportRequestHandler;
}
