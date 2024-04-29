#pragma once
#include "CommandBody.h"
#include "ResponseBody.h"

namespace Common
{
	class COMMON_LIB_API ChattingCommandBody : public CommandBody
	{
	public:
		std::string message;

	public:
		explicit ChattingCommandBody();

	protected:
		virtual void SerializeInternal(PacketStream& ps) override;
		virtual void DeserializeInternal(PacketStream& ps) override;
	};

	class COMMON_LIB_API ChattingResponseBody : public ResponseBody
	{
	public:
		std::string message;
		explicit ChattingResponseBody();

	protected:
		virtual void SerializeInternal(PacketStream& ps) override;
		virtual void DeserializeInternal(PacketStream& ps) override;
	};
}
