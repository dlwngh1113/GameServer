#pragma once
#include "Define.h"
#include "Packet.h"

namespace Common
{
	class COMMON_LIB_API ChattingPacket : public Packet
	{
	public:
		std::string message;

	public:
		explicit ChattingPacket();

	protected:
		virtual void SerializeInternal(PacketStream& ps) override;
		virtual void DeserializeInternal(PacketStream& ps) override;
	};
}
