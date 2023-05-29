#include "stdafx.h"
#include "LogoutRequestHandler.h"

void LogoutRequestHandler::HandleInGame()
{
	ClientCommon::LogoutRequest* packet = reinterpret_cast<ClientCommon::LogoutRequest*>(m_packet);
}

std::shared_ptr<BaseRequestHandler> LogoutRequestHandler::Create()
{
	return std::make_shared<LogoutRequestHandler>();
}
