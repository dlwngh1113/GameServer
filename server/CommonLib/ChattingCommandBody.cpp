#include "pch.h"
#include "ChattingCommandBody.h"

namespace Common
{
	ChattingCommandBody::ChattingCommandBody()
		: CommandBody(Command::Chatting)
	{
	}

	void ChattingCommandBody::SerializeInternal(PacketStream& ps)
	{
		ps.Write(message);
	}

	void ChattingCommandBody::DeserializeInternal(PacketStream& ps)
	{
		ps.Read(message);
	}
	
	//
	//
	//

	ChattingResponseBody::ChattingResponseBody()
		: ResponseBody(Command::Chatting)
	{
	}
	
	void ChattingResponseBody::SerializeInternal(PacketStream& ps)
	{
		ps.Write(message);
	}
	
	void ChattingResponseBody::DeserializeInternal(PacketStream& ps)
	{
		ps.Read(message);
	}
}