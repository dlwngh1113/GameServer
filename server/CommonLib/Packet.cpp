#include "pch.h"
#include "Packet.h"

namespace Common
{
	Packet::Packet(Command type)
		: m_type((short)type)
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
		ps >> header.type >> header.size;

		DeserializeInternal(ps);
	}
}