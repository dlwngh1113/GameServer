#include "pch.h"
#include "TeleportEventBody.h"

namespace Common
{
	TeleportEventBody::TeleportEventBody()
		: EventBody(Event::Teleport)
	{
	}

	void TeleportEventBody::SerializeInternal(PacketStream& ps)
	{
		ps.Write(userId);
		ps.Write(x);
		ps.Write(y);
	}

	void TeleportEventBody::DeserializeInternal(PacketStream& ps)
	{
		ps.Read(userId);
		ps.Read(x);
		ps.Read(y);
	}
}