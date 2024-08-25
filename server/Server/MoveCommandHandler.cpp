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
	//
	//

	m_user->Move(packet.x, packet.y);

	//
	// �̺�Ʈ �߼�
	//

	Common::MoveEventBody body;
	body.x = packet.x;
	body.y = packet.y;
	body.id = packet.id;
	body.userId = m_user->userId();
	body.moveTime = packet.moveTime;
	for (const auto& user : CServer::instance().users())
	{
		user.second->SendPacket(&body);
	}
}