#include "stdafx.h"
#include "MoveCommandHandler.h"
#include "User.h"
#include "CServer.h"

void MoveCommandHandler::HandleCommand()
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
	body.userId = m_user->userId();
	for (const auto& user : CServer::instance().users())
	{
		if (user.second != m_user)
			user.second->SendPacket(&body);
	}
}