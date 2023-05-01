#include "stdafx.h"
#include "LogoutRequestHandler.h"

void LogoutRequestHandler::HandleInGame()
{
	ClientCommon::LogoutRequest* packet = reinterpret_cast<ClientCommon::LogoutRequest*>(m_packet);
}

BaseRequestHandler* LogoutRequestHandler::Create()
{
	return new LogoutRequestHandler;
}
