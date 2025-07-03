#pragma once
#include "Define.h"
#include "PacketStream.h"

namespace Common
{
	class COMMON_LIB_API Packet
	{
	public:
		int16_t type;
		int16_t id;

	public:
		explicit Packet(int16_t type);

	public:
		virtual std::string Serialize(PacketStream& ps) final;
		virtual void Deserialize(PacketStream& ps) final;

	protected:
		virtual void SerializeInternal(PacketStream& ps) = 0;
		virtual void DeserializeInternal(PacketStream& ps) = 0;
	};
}
