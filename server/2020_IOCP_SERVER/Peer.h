#pragma once

namespace Core
{
	class BaseApplication;

	class Peer : enable_shared_from_this<Peer>
	{
	private:
		boost::asio::streambuf m_buffer;
		boost::asio::ip::tcp::socket m_socket;
		boost::uuids::uuid m_id;
		BaseApplication* m_application;

	public:
		Peer(boost::asio::io_context& context, BaseApplication* application);

		const boost::uuids::uuid& id() const;
		boost::asio::ip::tcp::socket& socket();

		void ReceiveData();
		void SendData(unsigned char* data, size_t size);

	protected:
		virtual void OnReceiveData(const boost::system::error_code& error, size_t size);

	private:
		void Disconnect();

		// Static Member Functions
	public:
		static shared_ptr<Peer> Create(boost::asio::io_context& context, BaseApplication* application);
	};
}