#include "pch.h"
#include "MoveCommandBody.h"

namespace Common
{
	MoveCommandBody::MoveCommandBody()
		: CommandBody(Command::Move)
		, x(0)
		, y(0)
	{
	}

	void MoveCommandBody::SerializeInternal(PacketStream& ps)
	{
		ps << x << y;
	}

	void MoveCommandBody::DeserializeInternal(PacketStream& ps)
	{
		ps >> x >> y;
	}

	MoveResponseBody::MoveResponseBody()
		: ResponseBody(Command::Move)
	{
	}

	void MoveResponseBody::SerializeInternal(PacketStream& ps)
	{
	}

	void MoveResponseBody::DeserializeInternal(PacketStream& ps)
	{
	}
}