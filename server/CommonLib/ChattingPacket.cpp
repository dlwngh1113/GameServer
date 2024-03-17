#include "pch.h"
#include "ChattingPacket.h"

namespace Common
{
	ChattingPacket::ChattingPacket()
		: Packet(Command::Chatting)
	{
	}

	void ChattingPacket::SerializeInternal(PacketStream& ps)
	{
		ps << message;
	}

	void ChattingPacket::DeserializeInternal(PacketStream& ps)
	{
		ps >> message;
	}
}