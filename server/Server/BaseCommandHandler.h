#pragma once
#include "Peer.h"

namespace Core
{
	static constexpr short kCode_Success = 0;
	static constexpr short kCode_Erorr = 1;

	class BaseCommandHandler
	{
	protected:
		Peer* m_peer;
		std::vector<uint8_t> m_data;

	public:
		BaseCommandHandler();
		virtual ~BaseCommandHandler();

		void Initialize(Peer* peer, const uint8_t* data, size_t size);

		virtual void Handle() = 0;

	protected:
		void SendResponse(Common::ResponseBody* response);
		void Error(short code, const std::string& message);
	};
}