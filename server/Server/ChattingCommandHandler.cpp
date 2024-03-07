#include "stdafx.h"
#include "ChattingCommandHandler.h"
#include "Logger.h"

void ChattingCommandHandler::HandleRequest()
{
	ClientCommon::ChattingPacket* packet = reinterpret_cast<ClientCommon::ChattingPacket*>(m_header);
}
