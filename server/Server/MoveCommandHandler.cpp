#include "stdafx.h"
#include "MoveCommandHandler.h"
#include "User.h"
#include "CServer.h"

void MoveCommandHandler::HandleRequest()
{
	Common::MoveCommandBody packet;
	Common::PacketStream ps(m_data.data(), m_data.size());
	packet.Deserialize(ps);

	//
	// 이벤트 발송
	//

	Common::MoveEventBody body;
	body.x = packet.x;
	body.y = packet.y;
	body.id = packet.id;
	for (const auto& user : CServer::instance().users())
	{
		user.second->SendPacket(&body);
	}
}