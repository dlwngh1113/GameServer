#include "stdafx.h"
#include "LoginCommandHandler.h"
#include "DataBase.h"
#include "Logger.h"
#include "CServer.h"
#include "User.h"

void LoginCommandHandler::HandleRequest()
{
	Common::LoginCommandBody body;
	Common::PacketStream ps(m_data.data(), m_data.size());
	body.Deserialize(ps);

	std::string id(body.userId);
	std::string password(body.password);

	std::shared_ptr<User> user = CServer::instance().GetUser(m_peer->id());
	if (!user)
	{
		Logger::instance().Log("����ڰ� �������� �ʽ��ϴ�.");
		return;
	}

	if (id.empty() || id.size() > 12)
	{
		Logger::instance().Log("ID�� ��ȿ���� �ʽ��ϴ�.");
		return;
	}

	if (password.empty() || password.size() > 20)
	{
		Logger::instance().Log(std::format("��й�ȣ�� ��ȿ���� �ʽ��ϴ�. password = {}", password));
		return;
	}

	float x{ 0 }, y{ 0 };

	try
	{
		std::unique_ptr<sql::PreparedStatement> stmt(Core::DataBase::instance().GetConnection()->prepareStatement("CALL GetUser(?,?)"));
		stmt->setString(1, id);
		stmt->setString(2, password);

		std::shared_ptr<sql::ResultSet> result(stmt->executeQuery());
		if (result->next())
			user->Login(result);
		else
			throw sql::SQLException{ "result is empty" };
	}
	catch (sql::SQLException& ex)
	{
		Logger::instance().Log(ex.getSQLState());
		return;
	}

	std::shared_ptr<Common::LoginResponseBody> resBody = std::make_shared<Common::LoginResponseBody>();
	resBody->id = body.id;
	resBody->x = user->x();
	resBody->y = user->y();
	
	SendResponse(resBody);
}
