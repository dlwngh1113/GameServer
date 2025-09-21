#include "pch.h"
#include "CommandBody.h"

namespace Common
{
	CommandBody::CommandBody(Command type)
		: Packet((int16_t)type)
	{
	}
	CommandBody::~CommandBody()
	{
	}
}