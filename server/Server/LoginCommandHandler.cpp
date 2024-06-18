#include "stdafx.h"
#include "LoginCommandHandler.h"
#include "DataBase.h"
#include "Logger.h"

void LoginCommandHandler::HandleRequest()
{
	Common::LoginCommandBody body;
	Common::PacketStream ps(m_data.data(), m_data.size());
	body.Deserialize(ps);

	std::string id(body.id);
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


}
