#include "stdafx.h"
#include "LoginRequestHandler.h"
#include "DBWorker.h"
#include "Place.h"
#include "User.h"
#include "Logger.h"

#define STRESS_TEST

std::shared_ptr<BaseRequestHandler> LoginRequestHandler::Create()
{
	return std::make_shared<LoginRequestHandler>();
}

void LoginRequestHandler::HandleRequest()
{
	ClientCommon::LoginRequest* packet = reinterpret_cast<ClientCommon::LoginRequest*>(m_packet);

	auto result =
#ifdef STRESS_TEST
		DBWorker::GetOrCreateUser(packet->name);
#else
		DBWorker::GetUser(packet->name);
#endif // STRESS_TEST

	if (result)
	{
		if (result->next())
		{
			m_user->SetInfo(result.get());

			// 응답 데이터 세팅

			ClientCommon::LoginResponse res;
			res.header.size = sizeof(ClientCommon::LoginResponse);
			res.header.type = static_cast<short>(ServerEvent::LoginOk);
			res.id = m_peer->GetID();
			res.level = m_user->GetLevel();
			res.exp = m_user->GetExp();
			res.x = m_user->GetX();
			res.y = m_user->GetY();
			res.hp = m_user->GetHp();
			res.placeId = m_user->GetPlace()->GetId();

			// 발송

			m_peer->SendPacket(&res);
		}
	}
	else
		throw RequestHandlerException{ LogFile, "해당 이름의 사용자가 없습니다." };
}