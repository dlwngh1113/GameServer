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
		ps << userId << x << y;
	}

	void TeleportEventBody::DeserializeInternal(PacketStream& ps)
	{
		ps >> userId >> x >> y;
	}
}