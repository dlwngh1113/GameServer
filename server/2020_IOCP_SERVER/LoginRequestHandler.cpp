#include"stdafx.h"
#include "LoginRequestHandler.h"
#include"CServer.h"
#include"DBWorker.h"
#include"MetaDatas.h"

BaseRequestHandler* LoginRequestHandler::Create()
{
	return new LoginRequestHandler;
}

void LoginRequestHandler::HandleRequest()
{
	LoginRequest* packet = reinterpret_cast<LoginRequest*>(m_packet);

	DBWorker::GetUser(m_user, packet->name);
	m_user->CompleteLogin();

	LoginResponse res;
	res.size = sizeof(LoginResponse);
	res.type = SC_PACKET_LOGIN_OK;
	res.id = m_peer->GetID();
	res.level = m_user->GetLevel();
	res.exp = m_user->GetExp();
	res.hp = m_user->GetHp();
	res.x = m_user->GetX();
	res.y = m_user->GetY();

	// 로그인 시 주변 유저를 줘야하는데 어떻게..?

	m_peer->SendPacket(&res);
}