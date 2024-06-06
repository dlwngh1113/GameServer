#include "stdafx.h"
#include "ChattingCommandHandler.h"
#include "Logger.h"
#include "CServer.h"
#include "User.h"

void ChattingCommandHandler::HandleRequest()
{
	Common::ChattingCommandBody packet;
	Common::PacketStream ps(m_data.data(), m_data.size());
	packet.Deserialize(ps);

	//
	// 이벤트 발송
	//

	Common::ChattingEventBody body;
	body.message = packet.message;
	body.id = packet.id;
	for (const auto& user : CServer::instance().users())
	{
		std::cout << user.second->id() << std::endl;
		user.second->SendPacket(&body);
	}
}
