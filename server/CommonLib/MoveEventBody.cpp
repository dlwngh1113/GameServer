#include "pch.h"
#include "MoveEventBody.h"

namespace Common
{
	MoveEventBody::MoveEventBody()
		: EventBody(Event::Move)
	{
	}

	MoveEventBody::~MoveEventBody()
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