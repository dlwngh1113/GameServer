#include "stdafx.h"
#include "LogoutRequestHandler.h"

void LogoutRequestHandler::HandleRequest()
{
	LogoutRequest* packet = reinterpret_cast<LogoutRequest*>(m_packet);
}

BaseRequestHandler* LogoutRequestHandler::Create()
{
	return new LogoutRequestHandler;
}
