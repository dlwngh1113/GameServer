#include "pch.h"
#include "Packet.h"

namespace Common
{
	Packet::Packet(short type)
		: type(type)
	{
	}

	std::string Packet::Serialize(PacketStream& ps)
	{
		SerializeInternal(ps);

		ps << id;

		return ps.GetData(type);
	}

	void Packet::Deserialize(PacketStream& ps)
	{
		Header header;
		ps >> header.type >> header.size >> id;

		DeserializeInternal(ps);
	}
}