#include "pch.h"
#include "MoveCommandBody.h"

namespace Common
{
	void MoveCommandBody::SerializeInternal(PacketStream& ps)
	{
		ps << x << y;
	}

	void MoveCommandBody::DeserializeInternal(PacketStream& ps)
	{
		ps >> x >> y;
	}

	void MoveResponseBody::SerializeInternal(PacketStream& ps)
	{
	}

	void MoveResponseBody::DeserializeInternal(PacketStream& ps)
	{
	}
}