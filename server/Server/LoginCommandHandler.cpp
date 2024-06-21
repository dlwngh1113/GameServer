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
		Logger::instance().Log("ID가 유효하지 않습니다.");
		return;
	}

	if (password.empty() || password.size() > 20)
	{
		Logger::instance().Log(std::format("비밀번호가 유효하지 않습니다. password = {}", password));
		return;
	}

	float x{ 0 }, y{ 0 };

	try
	{
		sql::PreparedStatement* stmt(Core::DataBase::instance().GetConnection()->prepareStatement("CALL GetUser(?,?)"));
		stmt->setString(1, id);
		stmt->setString(2, password);

		sql::ResultSet* result(stmt->executeQuery());
		while (result->next())
		{
			x = static_cast<float>(result->getDouble("x"));
			y = static_cast<float>(result->getDouble("y"));
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
