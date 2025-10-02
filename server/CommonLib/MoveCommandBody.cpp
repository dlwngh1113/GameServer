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

	MoveCommandBody::~MoveCommandBody()
	{
	}

	void MoveCommandBody::SerializeInternal(PacketStream& ps)
	{
		ps << x << y << moveTime;
	}

	void MoveCommandBody::DeserializeInternal(PacketStream& ps)
	{
		ps >> x >> y >> moveTime;
	}

	MoveResponseBody::MoveResponseBody()
		: ResponseBody(Command::Move)
	{
	}

	MoveResponseBody::~MoveResponseBody()
	{
	}

	void MoveResponseBody::SerializeInternal(PacketStream& ps)
	{
		ps << x << y << moveTime;
	}

	void MoveResponseBody::DeserializeInternal(PacketStream& ps)
	{
		ps >> x >> y >> moveTime;
	}
}