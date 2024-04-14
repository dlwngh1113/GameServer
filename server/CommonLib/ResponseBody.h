#pragma once
#include "Packet.h"

namespace Common
{
	class COMMON_LIB_API ResponseBody : public Packet
	{
	protected:
		short m_code;
		std::string m_message;

	protected:
		virtual void SerializeInternal(PacketStream& ps) override;
		virtual void DeserializeInternal(PacketStream& ps) override;

	public:
		explicit ResponseBody(Command type);
	};
}
