#pragma once
#include "Packet.h"

namespace Common
{
	class ChattingPacket : public Packet
	{
	public:
		std::string message;

	protected:
		virtual void SerializeInternal(PacketStream& ps) override;
		virtual void DeserializeInternal(PacketStream& ps) override;
	};
}
