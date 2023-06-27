#include "stdafx.h"
#include "LoginRequestHandler.h"
#include "DBWorker.h"
#include "Place.h"
#include "User.h"
#include "ConnectionPool.h"
#include "Logger.h"

#define STRESS_TEST

std::shared_ptr<BaseRequestHandler> LoginRequestHandler::Create()
{
	return std::make_shared<LoginRequestHandler>();
}

void LoginRequestHandler::HandleRequest()
{
	ClientCommon::LoginRequest* packet = reinterpret_cast<ClientCommon::LoginRequest*>(m_packet);

	auto statement =
#ifdef STRESS_TEST
		DBWorker::GetOrCreateUser(packet->name);
#else
		DBWorker::GetUser(packet->name);
#endif // STRESS_TEST

	std::unique_ptr<sql::ResultSet> result{ statement->executeQuery() };
	
	if (result->next())
	{
		do
		{
			m_user->SetInfo(result.get());

			// ���� ������ ����

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

			// �߼�

			m_peer->SendPacket(&res);
		} while (result->next());
	}
	else
		throw RequestHandlerException{ LogFile, "�ش� �̸��� ����ڰ� �����ϴ�." };

	while (statement->getMoreResults())
		statement->getResultSet();

	ConnectionPool::GetInstance().ReleaseConnection(statement->getConnection());
}