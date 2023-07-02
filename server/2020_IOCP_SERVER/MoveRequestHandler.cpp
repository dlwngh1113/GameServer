#include "stdafx.h"
#include "MoveRequestHandler.h"
#include "User.h"
#include "Place.h"

std::shared_ptr<BaseRequestHandler> MoveRequestHandler::Create()
{
	return std::make_shared<MoveRequestHandler>();
}

void MoveRequestHandler::HandleInGame()
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
		throw RequestHandlerException{ LogFile, "현재 장소가 없습니다." };

	place->Move(m_user.get(), x, y);

	// 발송

	ClientCommon::MoveResponse res;
	res.header.size = sizeof(ClientCommon::MoveResponse);
	res.header.type = static_cast<short>(ServerEvent::UserMove);
	res.id = m_user->GetID();
	res.x = m_user->GetX();
	res.y = m_user->GetY();
	res.move_time = packet->move_time;

	m_user->SendPacket(&res);
}