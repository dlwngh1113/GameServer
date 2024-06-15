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
	}

	void MoveEventBody::DeserializeInternal(PacketStream& ps)
	{
	}

}