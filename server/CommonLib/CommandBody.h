#pragma once
#include "Packet.h"

namespace Common
{
	class COMMON_LIB_API CommandBody : public Packet
	{
	public:
		explicit CommandBody(Command type);

	protected:
		virtual void DeserializeInternal(PacketStream& ps) = 0;
		virtual void SerializeInternal(PacketStream& ps) = 0;
	};
}
