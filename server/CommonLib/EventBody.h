#pragma once
#include "Packet.h"

namespace Common
{
	class COMMON_LIB_API EventBody : public Packet
	{
	public:
		explicit EventBody(Event type);

	protected:
		virtual void SerializeInternal(PacketStream& ps) override;
		virtual void DeserializeInternal(PacketStream& ps) override;
	};
}
