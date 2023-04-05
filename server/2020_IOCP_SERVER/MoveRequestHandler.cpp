#include "stdafx.h"
#include "MoveRequestHandler.h"
#include"User.h"
#include"Packets.h"
#include "Place.h"

BaseRequestHandler* MoveRequestHandler::Create()
{
	return new MoveRequestHandler;
}

void MoveRequestHandler::HandleRequest()
{
	MoveRequest* packet = reinterpret_cast<MoveRequest*>(m_packet);

	short x{ m_user->GetX() }, y{ m_user->GetY() };
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

	Place* place = m_user->GetPlace();
	if (place == nullptr)
		throw std::exception{ "���� ��Ұ� �����ϴ�." };

	place->Move(m_user, x, y);

	// �̺�Ʈ ������ ����

	UserMoveEvent ev;
	ev.size = sizeof(ev);
	ev.type = SC_PACKET_MOVE;
	ev.id = m_user->GetID();
	ev.x = m_user->GetX();
	ev.y = m_user->GetY();

	// �߼�

	//SendEvent(user, &ev);
	//m_user->GetPlace()->Move(m_user, x, y);

	MoveResponse res;
	res.size = sizeof(MoveResponse);
	res.type = SC_PACKET_MOVE;
	res.id = m_peer->GetID();
	res.x = m_user->GetX();
	res.y = m_user->GetY();
	res.move_time = packet->move_time;

	m_peer->SendPacket(&res);
}