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
		ps << userId << x << y << moveTime;
	}

	void MoveEventBody::DeserializeInternal(PacketStream& ps)
	{
		ps >> userId >> x >> y >> moveTime;
	}
}