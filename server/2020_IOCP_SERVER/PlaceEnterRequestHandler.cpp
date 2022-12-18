#include "stdafx.h"
#include "PlaceEnterRequestHandler.h"
#include"MetaDatas.h"

void PlaceEnterRequestHandler::HandleRequest()
{
	PlaceEnterRequest* packet = reinterpret_cast<PlaceEnterRequest*>(m_packet);
	Place* place = MetaDatas::GetInstance()->GetPlace(packet->placeId);

	place->AddUser(m_user);
	m_user->GetPlace() = place;

	// 응답 데이터 세팅

	PlaceEnterResponse res;
	res.size = sizeof(res);
	res.type = SC_PACKET_ENTER;
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
