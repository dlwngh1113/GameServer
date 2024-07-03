#include "stdafx.h"
#include "LoginCommandHandler.h"
#include "Logger.h"
#include "CServer.h"
#include "User.h"
#include "DBUtil.h"

void LoginCommandHandler::Handle()
{
	Common::LoginCommandBody body;
	Common::PacketStream ps(m_data.data(), m_data.size());
	body.Deserialize(ps);

	std::string id(body.userId);
	std::string password(body.password);

	std::shared_ptr<User> user = CServer::instance().GetUser(m_peer->id());
	if (!user)
	{
		Logger::instance().Log("사용자가 존재하지 않습니다.");
		return;
	}

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
	std::shared_ptr<sql::ResultSet> result = DBUtil::GetUser(id, password);
	if (!result)
		return;

	user->Login(result);

	std::shared_ptr<Common::LoginResponseBody> resBody = std::make_shared<Common::LoginResponseBody>();
	resBody->id = body.id;
	resBody->x = user->x();
	resBody->y = user->y();
	
	SendResponse(resBody);
}
