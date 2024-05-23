#include "stdafx.h"
#include "ChattingCommandHandler.h"
#include "Logger.h"
#include "CServer.h"
#include "User.h"

void ChattingCommandHandler::HandleRequest()
{
	Common::ChattingCommandBody packet;
	Common::PacketStream ps(reinterpret_cast<unsigned char*>(m_header), m_header->size);
	packet.Deserialize(ps);

	std::cerr << packet.message << std::endl;

	//
	// 이벤트 발송
	//

	//Common::ChattingResponseBody resBody;
	//resBody.type = (short)Event::Chatting;
	//resBody.message = packet.message;
	//resBody.id = packet.id;
	//for (const auto& user : CServer::instance().users())
	//{
	//	user.second->SendPacket(&resBody);
	//}
}
