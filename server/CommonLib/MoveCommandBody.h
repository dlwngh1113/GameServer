#pragma once
#include "CommandBody.h"
#include "ResponseBody.h"

namespace Common
{
	class COMMON_LIB_API MoveCommandBody : public CommandBody
	{
	public:
		float x, y;

	protected:
		virtual void SerializeInternal(PacketStream& ps);
		virtual void DeserializeInternal(PacketStream& ps);
	};

	class COMMON_LIB_API MoveResponseBody : public ResponseBody
	{
	protected:
		virtual void DeserializeInternal(PacketStream& ps);
		virtual void SerializeInternal(PacketStream& ps);
	};
}
