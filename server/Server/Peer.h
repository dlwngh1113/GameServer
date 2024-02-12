#pragma once
#include "Uuid.h"

namespace Core
{
	class BaseApplication;
	class BaseRequestHandlerFactory;

	class Peer final : public enable_shared_from_this<Peer>
	{
	private:
		boost::asio::ip::tcp::socket m_socket;

		vector<char> m_processBuffer;
		size_t m_bufferOffset;
		boost::asio::streambuf m_buffer;

		boost::uuids::uuid m_id;
		BaseApplication* m_application;
		BaseRequestHandlerFactory* m_factory;

	public:
		explicit Peer(boost::asio::ip::tcp::socket&& socket, BaseApplication* application) noexcept;

		const boost::uuids::uuid& id() const;

		void SendData(char* data, size_t size);
		void SetFactory(BaseRequestHandlerFactory* factory) { m_factory = factory; }

	protected:
		void OnReceiveData(const boost::system::error_code& error, size_t bytesTransferred);
		
	private:
		void ReceiveData();
		void ProcessPacket(char* data, size_t size);
		void ReceiveLeftData(char* currentReceivePtr, char* nextRecvPtr);
		void Disconnect();

		// Static Member Functions
	public:
		static shared_ptr<Peer> Create(boost::asio::ip::tcp::socket&& socket, BaseApplication* application);
	};
}