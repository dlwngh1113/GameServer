#include "stdafx.h"
#include "PlaceEnterRequestHandler.h"
#include"MetaDatas.h"
#include"User.h"
#include "Packets.h"

void PlaceEnterRequestHandler::HandleRequest()
{
	ClientCommon::PlaceEnterRequest* packet = reinterpret_cast<ClientCommon::PlaceEnterRequest*>(m_packet);
	Place* place = MetaDatas::GetInstance()->GetPlace(packet->placeId);

	place->AddUser(m_user);
	m_user->GetPlace() = place;

	// 응답 데이터 세팅

	ClientCommon::PlaceEnterResponse res;
	res.size = sizeof(res);
	res.type = static_cast<short>(ServerCommand::UserEnter);
	res.id = m_user->GetID();
	res.x = m_user->GetX();
	res.y = m_user->GetY();

	// 발송

	m_user->SendPacket(&res);
}

BaseRequestHandler* PlaceEnterRequestHandler::Create()
{
	return new PlaceEnterRequestHandler;
}
