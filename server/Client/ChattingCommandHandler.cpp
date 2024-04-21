#include "pch.h"
#include "ChattingCommandHandler.h"

void ChattingCommandHandler::Handle()
{
	Common::ChattingResponseBody* resBody = reinterpret_cast<Common::ChattingResponseBody*>(m_packet);
}
