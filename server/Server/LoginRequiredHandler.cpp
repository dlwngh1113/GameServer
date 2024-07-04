#include "stdafx.h"
#include "LoginRequiredHandler.h"
#include "CServer.h"
#include "Logger.h"

void LoginRequiredHandler::Handle()
{
	m_user = CServer::instance().GetUser(m_peer->id());
	if (!m_user)
	{
		Logger::instance().Log("User가 존재하지 않습니다.");
		return;
	}

	HandleCommand();
}
