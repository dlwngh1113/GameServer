#include "pch.h"
#include "ChattingEventHandler.h"
#include "NetworkManager.h"

using namespace ClientFramework;

void ChattingEventHandler::Handle()
{
	Common::ChattingResponseBody* resBody = reinterpret_cast<Common::ChattingResponseBody*>(m_packet);


}
