#pragma once
#include "CommandBody.h"
#include "ResponseBody.h"

namespace Common
{
	class COMMON_LIB_API MoveCommandBody : public CommandBody
	{
	public:
		float x, y;
		int moveTime;

	public:
		explicit MoveCommandBody();

	protected:
		virtual void SerializeInternal(PacketStream& ps) override;
		virtual void DeserializeInternal(PacketStream& ps) override;
	};

	class COMMON_LIB_API MoveResponseBody : public ResponseBody
	{
	public:
		explicit MoveResponseBody();

	protected:
		virtual void DeserializeInternal(PacketStream& ps) override;
		virtual void SerializeInternal(PacketStream& ps) override;
	};
}
