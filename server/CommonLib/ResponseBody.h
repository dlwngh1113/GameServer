#pragma once
#include "Packet.h"

namespace Common
{
	class COMMON_LIB_API ResponseBody : public Packet
	{
	public:
		short m_code;
		std::string m_message;

	public:
		explicit ResponseBody(Command type);

	protected:
		virtual void SerializeInternal(PacketStream& ps) override;
		virtual void DeserializeInternal(PacketStream& ps) override;
	};
}
