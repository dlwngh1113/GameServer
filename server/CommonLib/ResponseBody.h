#pragma once
#include "Packet.h"

namespace Common
{
	class ResponseBody : public Packet
	{
	private:
		char m_type;
		std::string m_message;

	protected:
		virtual void SerializeInternal(PacketStream& ps) override;
		virtual void DeserializeInternal(PacketStream& ps) override;
	};
}