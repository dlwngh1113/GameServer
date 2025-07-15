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

	m_user->setMoveTime(packet.moveTime);

	Place* place = CServer::instance().GetPlace();
	place->SetUserPosition(m_user, packet.x, packet.y);
}