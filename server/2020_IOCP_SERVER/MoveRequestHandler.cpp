#include "stdafx.h"
#include "MoveRequestHandler.h"
#include"CServer.h"

void MoveRequestHandler::HandleRequest()
{
	MoveRequest* packet = reinterpret_cast<MoveRequest*>(m_packet);
	if (m_user->lastMoveTime + 1 >= packet->move_time)
		return;
	m_user->lastMoveTime = packet->move_time;
	switch (packet->direction)
	{
	case MV_UP:
		m_user->y--;
		break;
	case MV_DOWN:
		m_user->y++;
		break;
	case MV_LEFT:
		m_user->x--;
		break;
	case MV_RIGHT:
		m_user->x++;
		break;
	}

	MoveResponse res;
	res.size = sizeof(MoveResponse);
	res.type = SC_PACKET_MOVE;
	res.id = m_peer->GetID();
	res.x = m_user->x;
	res.y = m_user->y;
	res.move_time = packet->move_time;

	m_peer->SendPacket(&res);
}

BaseRequestHandler* MoveRequestHandler::Create()
{
	return new MoveRequestHandler;
}
