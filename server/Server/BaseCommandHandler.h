#pragma once
#include "Peer.h"

namespace Core
{
	static constexpr short kCode_Success = 0;
	static constexpr short kCode_Erorr = 1;

	class BaseCommandHandler
	{
	protected:
		std::shared_ptr<Peer> m_peer;
		std::vector<unsigned char> m_data;

	public:
		BaseCommandHandler();
		virtual ~BaseCommandHandler();

		void Initialize(std::shared_ptr<Peer> peer, unsigned char* data, size_t size);

		virtual void Handle() = 0;

	protected:
		void SendResponse(std::shared_ptr<Common::ResponseBody> response);
		void Error(short code, const std::string& message);
	};
}