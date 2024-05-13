#include "pch.h"
#include "EventBody.h"

namespace Common
{
	EventBody::EventBody(Event type)
		: Packet((short)type)
	{
	}

	void EventBody::SerializeInternal(PacketStream& ps)
	{
	}
	
	void EventBody::DeserializeInternal(PacketStream& ps)
	{
	}
}
