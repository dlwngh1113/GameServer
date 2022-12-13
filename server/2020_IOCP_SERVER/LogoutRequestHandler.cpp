#include "stdafx.h"
#include "LogoutRequestHandler.h"
#include"CServer.h"

void LogoutRequestHandler::HandleRequest()
{
	LogoutRequest* packet = reinterpret_cast<LogoutRequest*>(m_packet);
	m_user->GetPlace()->RemoveUser(m_user);
}

BaseRequestHandler* LogoutRequestHandler::Create()
{
	return new LogoutRequestHandler;
}
