#include "pch.h"
#include "ChattingEventBody.h"

namespace Common
{
	ChattingEventBody::ChattingEventBody()
		: EventBody(Event::Chatting)
	{
	}

	void ChattingEventBody::SerializeInternal(PacketStream& ps)
	{
		ps.Write(message);
	}

	void ChattingEventBody::DeserializeInternal(PacketStream& ps)
	{
		ps.Read(message);
	}
}