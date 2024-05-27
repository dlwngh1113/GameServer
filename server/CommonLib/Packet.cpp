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

		return ps.GetData(id, type);
	}

	void Packet::Deserialize(PacketStream& ps)
	{
		Header header;
		ps >> type >> header.size >> id;

		DeserializeInternal(ps);
	}
}