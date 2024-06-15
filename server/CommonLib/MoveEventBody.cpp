#include "pch.h"
#include "MoveEventBody.h"

namespace Common
{
	MoveEventBody::MoveEventBody()
		: EventBody(Event::Move)
	{
	}

	void MoveEventBody::SerializeInternal(PacketStream& ps)
	{
		ps << x << y;
	}

	void MoveEventBody::DeserializeInternal(PacketStream& ps)
	{
		ps >> x >> y;
	}

}