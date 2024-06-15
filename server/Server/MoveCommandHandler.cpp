#include "stdafx.h"
#include "MoveCommandHandler.h"

void MoveCommandHandler::HandleRequest()
{
	Common::MoveCommandBody packet;
	Common::PacketStream ps(m_data.data(), m_data.size());
	packet.Deserialize(ps);

	//
	// 이벤트 발송
	//


}