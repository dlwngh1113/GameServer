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

	if (id.empty() || id.size() < 12)
	{
		Logger::instance().Log("ID가 유효하지 않습니다.");
		return;
	}

	if (password.empty())
	{
		Logger::instance().Log("비밀번호가 유효하지 않습니다.");
		return;
	}

	sql::PreparedStatement* stmt(Core::DataBase::instance().GetConnection()->prepareStatement("CALL GetUser(?,?)"));
	sql::ResultSet* result(stmt->executeQuery());

	float x(result->getDouble("x"));
	float y(result->getDouble("y"));

	Common::LoginResponseBody resBody;
	resBody.id = body.id;
	resBody.x = x;
	resBody.y = y;
	
	std::shared_ptr<User> user = CServer::instance().GetUser(m_peer->id());
	if (user)
		user->SendPacket(&resBody);
}
