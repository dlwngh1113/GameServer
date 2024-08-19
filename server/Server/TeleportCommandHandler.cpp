#include "stdafx.h"
#include "TeleportCommandHandler.h"
#include "Logger.h"

void TeleportCommandHandler::HandleCommand()
{
	Common::TeleportCommandBody packet;
	Common::PacketStream ps(m_data.data(), m_data.size());
	packet.Deserialize(ps);

	//
	//
	//

	if (packet.x < 0 || packet.x > 900 || packet.y < 0 || packet.y > 900)
	{
		Logger::instance().Log(std::format("위치가 유효하지 않습니다."));
		return;
	}


}
