#include"stdafx.h"
#include "LoginRequestHandler.h"
#include"DBWorker.h"
#include"Place.h"
#include"User.h"

BaseRequestHandler* LoginRequestHandler::Create()
{
	return new LoginRequestHandler;
}

void LoginRequestHandler::HandleRequest()
{
	LoginRequest* packet = reinterpret_cast<LoginRequest*>(m_packet);

	DBWorker::GetUser(m_user, packet->name);

	// 응답 데이터 세팅

	LoginResponse res;
	res.size = sizeof(LoginResponse);
	res.type = SC_PACKET_LOGIN_OK;
	res.id = m_peer->GetID();
	res.level = m_user->GetLevel();
	res.exp = m_user->GetExp();
	res.hp = m_user->GetHp();
	res.placeId = m_user->GetPlace()->GetId();

	// 발송

	m_peer->SendPacket(&res);
}