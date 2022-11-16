#include "stdafx.h"
#include "MoveRequestHandler.h"
#include"CServer.h"

void MoveRequestHandler::HandleRequest()
{
	MoveRequest* packet = reinterpret_cast<MoveRequest*>(m_packet);
	User* user = CServer::GetInstance()->GetUser(m_peer->GetID());
	if (user->lastMoveTime + 1 >= packet->move_time)
		return;
	user->lastMoveTime = packet->move_time;
	switch (packet->direction)
	{
	case MV_UP:
		user->y--;
		break;
	case MV_DOWN:
		user->y++;
		break;
	case MV_LEFT:
		user->x--;
		break;
	case MV_RIGHT:
		user->x++;
		break;
	}

	MoveResponse* res = new MoveResponse();
	res->size = sizeof(MoveResponse);
	res->type = SC_PACKET_MOVE;
	res->id = m_peer->GetID();
	res->x = user->x;
	res->y = user->y;
	res->move_time = packet->move_time;

	m_peer->SendPacket(res);
}

BaseRequestHandler* MoveRequestHandler::Create()
{
	return new MoveRequestHandler;
}
