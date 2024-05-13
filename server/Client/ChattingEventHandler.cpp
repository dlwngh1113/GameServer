#include "pch.h"
#include "ChattingEventHandler.h"

void ChattingEventHandler::Handle()
{
	Common::ChattingResponseBody* resBody = reinterpret_cast<Common::ChattingResponseBody*>(m_packet);
}
