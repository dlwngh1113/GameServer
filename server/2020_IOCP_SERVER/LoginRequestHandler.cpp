#include"stdafx.h"
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

	DBWorker::GetUser(m_user, packet->name);
	//auto dbc = DBWorker::GetUser(packet->name);

	//if (dbc)
	//	m_user->SetInfo(dbc.get());
	//else
	//	m_user->SetInfo(packet->name, 1, 0, 50, 0, 0, 0);

	// ���� ������ ����

	ClientCommon::LoginResponse res;
	res.size = sizeof(ClientCommon::LoginResponse);
	res.type = ClientCommon::SC_PACKET_LOGIN_OK;
	res.id = m_peer->GetID();
	res.level = m_user->GetLevel();
	res.exp = m_user->GetExp();
	res.hp = m_user->GetHp();
	res.placeId = m_user->GetPlace()->GetId();

	// �߼�

	m_peer->SendPacket(&res);
}