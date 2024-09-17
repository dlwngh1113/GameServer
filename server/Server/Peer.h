#pragma once
#include "Uuid.h"

namespace Core
{
	class BaseApplication;
	class BaseCommandHandlerFactory;

	class Peer final : public std::enable_shared_from_this<Peer>
	{
	private:
		boost::asio::ip::tcp::socket m_socket;

		unsigned char m_data[MAX_BUFFER]{};
		boost::asio::mutable_buffer m_buffer;
		unsigned char* m_currentReceivePos;

		boost::uuids::uuid m_id;
		BaseApplication* m_application;
		BaseCommandHandlerFactory* m_factory;

	public:
		explicit Peer(boost::asio::ip::tcp::socket&& socket, BaseApplication* application) noexcept;

		const boost::uuids::uuid& id() const;

		void SendData(std::shared_ptr<Common::Packet> packet);
		void SendData(const std::string& data);
		void SendData(char* data, size_t size);
		void SetFactory(BaseCommandHandlerFactory* factory) { m_factory = factory; }

	protected:
		void OnReceiveData(const boost::system::error_code& error, size_t bytesTransferred);
		
	private:
		void ReceiveData();
		void ProcessPacket(unsigned char* data, size_t size);
		void ReceiveLeftData(unsigned char* nextRecvPtr);
		void Disconnect();

		// Static Member Functions
	public:
		static std::shared_ptr<Peer> Create(boost::asio::ip::tcp::socket&& socket, BaseApplication* application);
	};
}