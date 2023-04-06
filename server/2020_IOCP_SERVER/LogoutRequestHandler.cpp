#include "stdafx.h"
#include "LogoutRequestHandler.h"

void LogoutRequestHandler::HandleRequest()
{
	ClientCommon::LogoutRequest* packet = reinterpret_cast<ClientCommon::LogoutRequest*>(m_packet);
}

BaseRequestHandler* LogoutRequestHandler::Create()
{
	return new LogoutRequestHandler;
}
