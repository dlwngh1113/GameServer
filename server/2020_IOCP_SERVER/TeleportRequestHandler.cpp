#include "stdafx.h"
#include "TeleportRequestHandler.h"
#include "User.h"
#include "Packets.h"
#include "CServer.h"

void TeleportRequestHandler::HandleRequest()
{
	ClientCommon::TeleportRequest* packet = reinterpret_cast<ClientCommon::TeleportRequest*>(m_packet);

	m_user->SetPosition(packet->x, packet->y);

	// �̺�Ʈ ������ ����

	ClientCommon::TeleportResponse res;
	res.size = sizeof(ClientCommon::TeleportResponse);
	res.type = ServerCommand::SC_PACKET_MOVE;

	// �߼�

	m_peer->SendPacket(&res);
}

BaseRequestHandler* TeleportRequestHandler::Create()
{
	return new TeleportRequestHandler;
}
