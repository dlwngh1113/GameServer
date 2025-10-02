#include "pch.h"
#include "EventBody.h"

namespace Common
{
	EventBody::EventBody(Event type)
		: Packet((int16_t)type)
	{
	}

	void EventBody::SerializeInternal(PacketStream& ps)
	{
	}
	
	void EventBody::DeserializeInternal(PacketStream& ps)
	{
	}
}
