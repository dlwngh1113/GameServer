#include "stdafx.h"
#include "ChattingCommandHandler.h"

void ChattingCommandHandler::HandleRequest()
{
	ClientCommon::ChattingPacket* packet = reinterpret_cast<ClientCommon::ChattingPacket*>(m_header);

	cout << packet->message << endl;
}
