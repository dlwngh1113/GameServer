#include "stdafx.h"
#include "MoveRequestHandler.h"
#include"CServer.h"

BaseRequestHandler* MoveRequestHandler::Create()
{
	return new MoveRequestHandler;
}

void MoveRequestHandler::HandleRequest()
{
	MoveRequest* packet = reinterpret_cast<MoveRequest*>(m_packet);

	short x{ 0 }, y{ 0 };
	switch (packet->direction)
	{
	case MV_UP:
		--y;
		break;
	case MV_DOWN:
		++y;
		break;
	case MV_LEFT:
		--x;
		break;
	case MV_RIGHT:
		++x;
		break;
	}

	m_user->Move(x, y, packet->move_time);

	MoveResponse res;
	res.size = sizeof(MoveResponse);
	res.type = SC_PACKET_MOVE;
	res.id = m_peer->GetID();
	res.x = m_user->GetX();
	res.y = m_user->GetY();
	res.move_time = packet->move_time;

	m_peer->SendPacket(&res);
}