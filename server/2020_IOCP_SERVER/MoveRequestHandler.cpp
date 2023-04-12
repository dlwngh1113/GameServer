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
	ClientCommon::MoveRequest* packet = reinterpret_cast<ClientCommon::MoveRequest*>(m_packet);

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

	ClientCommon::UserMoveEvent ev;
	ev.size = sizeof(ev);
	ev.type = static_cast<short>(ServerCommand::UserMove);
	ev.id = m_user->GetID();
	ev.x = m_user->GetX();
	ev.y = m_user->GetY();

	// �߼�

	//SendEvent(user, &ev);
	//m_user->GetPlace()->Move(m_user, x, y);

	ClientCommon::MoveResponse res;
	res.size = sizeof(ClientCommon::MoveResponse);
	res.type = static_cast<short>(ServerCommand::UserMove);
	res.id = m_peer->GetID();
	res.x = m_user->GetX();
	res.y = m_user->GetY();
	res.move_time = packet->move_time;

	m_peer->SendPacket(&res);
}