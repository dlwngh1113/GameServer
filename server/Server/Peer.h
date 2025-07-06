#pragma once
#include "Uuid.h"
#include "RingBuffer.h"

namespace Core
{
	class BaseApplication;
	class BaseCommandHandler;
	class BaseCommandHandlerFactory;

	class Peer final : public std::enable_shared_from_this<Peer>
	{
	private:
		boost::asio::ip::tcp::socket m_socket;

		RingBuffer m_buffer;

		boost::uuids::uuid m_id;
		BaseApplication* m_application;
		BaseCommandHandlerFactory* m_factory;

	public:
		explicit Peer(boost::asio::ip::tcp::socket&& socket, BaseApplication* application) noexcept;
		virtual ~Peer() noexcept;

		const boost::uuids::uuid& id() const;

		void SendData(std::shared_ptr<Common::Packet> packet);
		void SendData(const std::string& data);
		void SendData(char* data, size_t size);
		void SetFactory(BaseCommandHandlerFactory* factory) { m_factory = factory; }

	protected:
		void OnReceiveData(const boost::system::error_code& error, uint64_t bytesTransferred);
		
	private:
		void ReceiveData();
		void ProcessPacket(int16_t type, int16_t size);
		void ReceiveLeftData(uint8_t* nextRecvPtr);
		void Disconnect();

		// Static Member Functions
	public:
		static std::shared_ptr<Peer> Create(boost::asio::ip::tcp::socket&& socket, BaseApplication* application);
	};
}