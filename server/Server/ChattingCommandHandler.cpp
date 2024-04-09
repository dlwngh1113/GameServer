#include "stdafx.h"
#include "ChattingCommandHandler.h"
#include "Logger.h"

void ChattingCommandHandler::HandleRequest()
{
	Common::ChattingPacket packet;
	Common::PacketStream ps(reinterpret_cast<unsigned char*>(m_header), m_header->size);
	packet.Deserialize(ps);

	std::cerr << packet.message << std::endl;

}
