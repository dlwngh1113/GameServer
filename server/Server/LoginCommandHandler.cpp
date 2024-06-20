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

	if (id.empty() || id.size() > 12)
	{
		Logger::instance().Log("ID�� ��ȿ���� �ʽ��ϴ�.");
		return;
	}

	if (password.empty())
	{
		Logger::instance().Log("��й�ȣ�� ��ȿ���� �ʽ��ϴ�.");
		return;
	}

	Logger::instance().Log(std::format("id = {} password = {}", id, password));
	float x{ 0 }, y{ 0 };

	try
	{
		sql::PreparedStatement* stmt(Core::DataBase::instance().GetConnection()->prepareStatement("CALL GetUser(?,?)"));
		stmt->setQueryAttrString("p_name", id);
		stmt->setQueryAttrString("p_password", password);

		sql::ResultSet* result(stmt->executeQuery());
		while (result->next())
		{
			x = result->getDouble("x");
			y = result->getDouble("y");
		}
	}
	catch (sql::SQLException& ex)
	{
		Logger::instance().Log(ex.getSQLState());
	}

	Common::LoginResponseBody resBody;
	resBody.id = body.id;
	resBody.x = x;
	resBody.y = y;
	
	std::shared_ptr<User> user = CServer::instance().GetUser(m_peer->id());
	if (user)
		user->SendPacket(&resBody);
}
