#include "pch.h"
#include "LoginCommandBody.h"

namespace Common
{
	LoginCommandBody::LoginCommandBody()
		: CommandBody(Command::Login)
	{
	}

	LoginCommandBody::~LoginCommandBody()
	{
	}

	void LoginCommandBody::SerializeInternal(PacketStream& ps)
	{
		ps << userId << password;
	}

	void LoginCommandBody::DeserializeInternal(PacketStream& ps)
	{
		ps >> userId >> password;
	}

	//
	//
	//

	LoginResponseBody::LoginResponseBody()
		: ResponseBody(Command::Login)
		, x(0), y(0)
	{
	}

	LoginResponseBody::~LoginResponseBody()
	{
	}

	void LoginResponseBody::SerializeInternal(PacketStream& ps)
	{
		ps << x << y;
	}

	void LoginResponseBody::DeserializeInternal(PacketStream& ps)
	{
		ps >> x >> y;
	}
}