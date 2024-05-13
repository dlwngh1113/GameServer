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
		ps << message;
	}

	void ChattingCommandBody::DeserializeInternal(PacketStream& ps)
	{
		ps >> message;
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
		ps << message;
	}
	
	void ChattingResponseBody::DeserializeInternal(PacketStream& ps)
	{
		ps >> message;
	}
}