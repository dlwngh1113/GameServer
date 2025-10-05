#pragma once
#include "Uuid.h"

namespace Core
{
	class BaseApplication;
	class BaseCommandHandler;
	class BaseCommandHandlerFactory;

	class Peer final
	{
	private:
		boost::asio::ip::tcp::socket m_socket;

		Common::RingBuffer m_buffer;

		boost::uuids::uuid m_id;
		BaseApplication* m_application;
		BaseCommandHandlerFactory* m_factory;

	public:
		explicit Peer(boost::asio::ip::tcp::socket&& socket, BaseApplication* application) noexcept;
		virtual ~Peer() noexcept;

		const boost::uuids::uuid& id() const;

		void SendData(Common::Packet* packet);
		void SendData(const std::string& data);
		void SendData(char* data, size_t size);
		void SetFactory(BaseCommandHandlerFactory* factory) { m_factory = factory; }

	protected:
		void OnReceiveData(const boost::system::error_code& error, int32_t bytesTransferred);
		
	private:
		void ReceiveData();
		void ProcessPacket(int16_t type, int16_t size);
		void Disconnect();

		// Static Member Functions
	public:
		static Peer* Create(boost::asio::ip::tcp::socket&& socket, BaseApplication* application);
	};
}