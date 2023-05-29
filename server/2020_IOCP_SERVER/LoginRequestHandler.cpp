#include "stdafx.h"
#include "LoginRequestHandler.h"
#include "DBWorker.h"
#include "DBConnector.h"
#include "Place.h"
#include "User.h"

std::shared_ptr<BaseRequestHandler> LoginRequestHandler::Create()
{
	return std::make_shared<LoginRequestHandler>();
}

void LoginRequestHandler::HandleRequest()
{
	ClientCommon::LoginRequest* packet = reinterpret_cast<ClientCommon::LoginRequest*>(m_packet);

	auto result = DBWorker::GetUser(packet->name);
	if (result)
	{
		m_user->SetInfo(result.get());

		// ���� ������ ����

		ClientCommon::LoginResponse res;
		res.header.size = sizeof(ClientCommon::LoginResponse);
		res.header.type = static_cast<short>(ServerCommand::LoginOk);
		res.id = m_peer->GetID();
		res.level = m_user->GetLevel();
		res.exp = m_user->GetExp();
		res.hp = m_user->GetHp();
		res.placeId = m_user->GetPlace()->GetId();

		// �߼�

		m_peer->SendPacket(&res);
	}
}