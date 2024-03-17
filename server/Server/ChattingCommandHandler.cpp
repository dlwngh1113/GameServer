#include "stdafx.h"
#include "ChattingCommandHandler.h"
#include "Logger.h"
#include "Peer.h"

void ChattingCommandHandler::HandleRequest()
{
	Common::ChattingPacket packet;
	Common::PacketStream ps(reinterpret_cast<unsigned char*>(m_header), m_header->size);
	packet.Deserialize(ps);

	cerr << packet.message << endl;

}
