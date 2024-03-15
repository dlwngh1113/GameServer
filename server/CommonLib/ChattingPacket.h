#pragma once
#include "Packet.h"

namespace Common
{
	class ChattingPacket : public Packet
	{
	public:
		std::string message;

	protected:
		virtual void SerializeInternal() override;
		virtual void DeserializeInternal() override;
	};
}
