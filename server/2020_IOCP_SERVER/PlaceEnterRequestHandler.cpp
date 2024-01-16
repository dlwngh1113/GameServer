#include "stdafx.h"
#include "PlaceEnterRequestHandler.h"
#include "MetaDatas.h"
#include "User.h"

void PlaceEnterRequestHandler::HandleInGame()
{
	ClientCommon::PlaceEnterRequest* packet = reinterpret_cast<ClientCommon::PlaceEnterRequest*>(m_packet);
	Place* place = MetaDatas::GetInstance().GetPlace(packet->placeId);

	place->AddUser(m_user.get());
	m_user->GetPlace() = place;

	// ���� ������ ����

	ClientCommon::PlaceEnterResponse res;
	res.header.size = sizeof(res);
	res.header.type = static_cast<short>(ServerEvent::UserEnter);
	res.id = m_user->GetID();
	res.x = m_user->GetX();
	res.y = m_user->GetY();

	// �߼�

	m_user->SendPacket(&res);
}
