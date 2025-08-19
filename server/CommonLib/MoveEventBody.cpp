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
		ps.Write(userId);
		ps.Write(x);
		ps.Write(y);
		ps.Write(moveTime);
	}

	void MoveEventBody::DeserializeInternal(PacketStream& ps)
	{
		ps.Read(userId);
		ps.Read(x);
		ps.Read(y);
		ps.Read(moveTime);
	}
}