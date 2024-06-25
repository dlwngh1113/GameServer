#include "stdafx.h"
#include "CommandHandler.h"
#include "CServer.h"

void CommandHandler::Handle()
{
	HandleRequest();
}

void CommandHandler::SendResponse(std::shared_ptr<Common::Packet> packet)
{
	Common::PacketStream ps;
	std::string data = packet->Serialize(ps);

	m_peer->SendData(data);
}
