#include "pch.h"
#include "Packet.h"

namespace Common
{
	Packet::Packet(short type)
		: m_type(type)
	{
	}

	std::string Packet::Serialize(PacketStream& ps)
	{
		SerializeInternal(ps);

		return ps.GetData(m_type);
	}

	void Packet::Deserialize(PacketStream& ps)
	{
		Header header;
		ps >> header;

		DeserializeInternal(ps);
	}
}