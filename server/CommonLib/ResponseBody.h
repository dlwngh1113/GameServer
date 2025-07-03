#pragma once
#include "Packet.h"

namespace Common
{
	class COMMON_LIB_API ResponseBody : public Packet
	{
	public:
		int16_t code;
		std::string message;

	public:
		explicit ResponseBody(Command type);

	protected:
		virtual void SerializeInternal(PacketStream& ps) override;
		virtual void DeserializeInternal(PacketStream& ps) override;
	};
}
