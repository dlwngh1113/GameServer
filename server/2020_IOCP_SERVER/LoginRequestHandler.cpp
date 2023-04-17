#include "stdafx.h"
#include "LoginRequestHandler.h"
#include "DBWorker.h"
#include "DBConnector.h"
#include "Place.h"
#include "User.h"

BaseRequestHandler* LoginRequestHandler::Create()
{
	return new LoginRequestHandler;
}

void LoginRequestHandler::HandleRequest()
{
	ClientCommon::LoginRequest* packet = reinterpret_cast<ClientCommon::LoginRequest*>(m_packet);

	sql::ResultSet* result = DBWorker::GetUser(packet->name);
	if (result->rowsCount() <= 0)
	{
		DBWorker::AddUser(packet->name);
		result = DBWorker::GetUser(packet->name);
	}
	m_user->SetInfo(result);

	delete result;

	// 응답 데이터 세팅

	ClientCommon::LoginResponse res;
	res.size = sizeof(ClientCommon::LoginResponse);
	res.type = static_cast<short>(ServerCommand::LoginOk);
	res.id = m_peer->GetID();
	res.level = m_user->GetLevel();
	res.exp = m_user->GetExp();
	res.hp = m_user->GetHp();
	res.placeId = m_user->GetPlace()->GetId();

	// 발송

	m_peer->SendPacket(&res);
}