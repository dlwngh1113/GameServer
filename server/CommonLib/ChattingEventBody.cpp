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
		ps << message;
	}

	void ChattingEventBody::DeserializeInternal(PacketStream& ps)
	{
		ps >> message;
	}
}