#pragma once
#include "PacketStream.h"

namespace Common
{
	class Packet
	{
	protected:
		short m_type;

	public:
		explicit Packet(short type);

	public:
		virtual std::string Serialize(PacketStream& ps) final;
		virtual void Deserialize(PacketStream& ps) final;

	protected:
		virtual void SerializeInternal(PacketStream& ps) = 0;
		virtual void DeserializeInternal(PacketStream& ps) = 0;
	};
}
