#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <thread>
#include <vector>
#include <unordered_set>
#include <mutex>
#include <atomic>
#include <chrono>
#include <queue>
#include <array>
#include <memory>
#include <unordered_map>
#include <boost/asio.hpp>
#include <boost/uuid/uuid.hpp>

using namespace std;
using namespace chrono;
using namespace boost::asio::ip;

const static int MAX_TEST = 10000;
const static int MAX_CLIENTS = MAX_TEST * 2;
const static int INVALID_ID = -1;
const static int MAX_PACKET_SIZE = 255;
const static int MAX_BUFF_SIZE = 255;

#pragma comment (lib, "ws2_32.lib")
#include "../../server/Common/Common.hpp"

using namespace ClientCommon;

enum OPTYPE { OP_SEND, OP_RECV, OP_DO_MOVE };

high_resolution_clock::time_point last_connect_time;

struct CLIENT
{
	int id;
	int x;
	int y;
	atomic_bool connected;

	tcp::socket client_socket;
	unsigned char packet_buf[MAX_PACKET_SIZE];
	int prev_packet_data;
	int curr_packet_size;
	high_resolution_clock::time_point last_move_time;
};

boost::asio::io_context g_context;
tcp::resolver g_resolver;
tcp::resolver::query g_query(tcp::v4(), "127.0.0.1:3500");
array<CLIENT, MAX_CLIENTS> g_clients;
unordered_map<boost::uuids::uuid, shared_ptr<CLIENT>> s_clients;
atomic_int num_connections;
atomic_int client_to_close;
atomic_int active_clients;

int			global_delay;				// ms단위, 1000이 넘으면 클라이언트 증가 종료

vector <thread*> worker_threads;
thread test_thread;

float point_cloud[MAX_TEST * 2];

// 나중에 NPC까지 추가 확장 용
struct ALIEN
{
	int id;
	int x, y;
	int visible_count;
};

void error_display(const char* msg, int err_no)
{
	WCHAR* lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, err_no,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	std::cout << msg;
	std::wcout << L"에러" << lpMsgBuf << std::endl;

	LocalFree(lpMsgBuf);
	// while (true);
}

void DisconnectClient(int ci)
{
	bool status = true;
	if (true == atomic_compare_exchange_strong(&g_clients[ci].connected, &status, false))
	{
		g_clients[ci].client_socket.close();
		active_clients--;
	}
	// cout << "Client [" << ci << "] Disconnected!\n";
}

void SendPacket(int cl, Packet* packet)
{
	int psize = packet->header.size;
	int ptype = packet->header.type;

	string p;
	p.resize(psize);
	memcpy(&p[0], packet, psize);
	boost::asio::async_write(g_clients[cl].client_socket, boost::asio::buffer(p),
		[](const boost::system::error_code& error, size_t bytes) {});
}

void ProcessPacket(int ci, unsigned char packet[])
{
	Packet* p = reinterpret_cast<Packet*>(packet);
	ServerEvent evt = static_cast<ServerEvent>(p->header.type);

	switch (evt) {
	//case ServerEvent::UserMove:
	//{
	//	MoveResponse* move_packet = reinterpret_cast<MoveResponse*>(packet);
	//	if (move_packet->id < MAX_CLIENTS)
	//	{
	//		int my_id = client_map[move_packet->id];
	//		if (-1 != my_id) 
	//		{
	//			g_clients[my_id].x = move_packet->x;
	//			g_clients[my_id].y = move_packet->y;
	//		}
	//		if (ci == my_id)
	//		{
	//			if (0 != move_packet->move_time)
	//			{
	//				auto d_ms = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count() - move_packet->move_time;

	//				if (global_delay < d_ms) global_delay++;
	//				else if (global_delay > d_ms) global_delay--;
	//			}
	//		}
	//	}
	//}
	//				   break;
	//case ServerEvent::UserEnter: break;
	//case ServerEvent::UserExit: break;
	//case ServerEvent::LoginOk:
	//{
	//	g_clients[ci].connected = true;
	//	active_clients++;
	//	LoginResponse* login_packet = reinterpret_cast<LoginResponse*>(packet);
	//	int my_id = ci;
	//	client_map[login_packet->id] = my_id;
	//	g_clients[my_id].id = login_packet->id;
	//	g_clients[my_id].x = login_packet->x;
	//	g_clients[my_id].y = login_packet->y;

	//	TeleportRequest t_packet;
	//	t_packet.x = rand() % WORLD_WIDTH;
	//	t_packet.y = rand() % WORLD_HEIGHT;
	//	t_packet.header.size = sizeof(t_packet);
	//	t_packet.header.type = static_cast<short>(ClientCommand::Teleport);
	//	SendPacket(my_id, &t_packet);
	//}
	break;
	//case SC_PACKET_CHAT:
	//	break;
	//case SC_PACKET_STAT_CHANGE:
	//	break;
	default:
		while (true);
	}
}

constexpr int DELAY_LIMIT = 100;
constexpr int DELAY_LIMIT2 = 150;
constexpr int ACCEPT_DELY = 50;

void OnReceive(const boost::system::error_code& error, size_t bytes)
{
	if (!error)
	{
		// packet process
			unsigned char* buf = g_clients[ci].recv_over.IOCP_buf;
			unsigned psize = g_clients[ci].curr_packet_size;
			unsigned pr_size = g_clients[ci].prev_packet_data;
			while (io_size > 0) 
			{
				if (io_size < sizeof(Header))
				{
					memcpy(g_clients[ci].packet_buf + pr_size, buf, io_size);
					pr_size += io_size;
					io_size = 0;
				}
				else
				{
					Packet* bp = reinterpret_cast<Packet*>(buf);
					psize = bp->header.size;

					if (io_size + pr_size >= psize)
					{
						// 지금 패킷 완성 가능
						unsigned char packet[MAX_PACKET_SIZE];
						memcpy(packet, g_clients[ci].packet_buf, pr_size);
						memcpy(packet + pr_size, buf, psize - pr_size);
						ProcessPacket(static_cast<int>(ci), packet);
						io_size -= psize - pr_size;
						buf += psize - pr_size;
						psize = 0; pr_size = 0;
					}
					else
					{
						memcpy(g_clients[ci].packet_buf + pr_size, buf, io_size);
						pr_size += io_size;
						io_size = 0;
					}
				}
			}
			g_clients[ci].curr_packet_size = psize;
			g_clients[ci].prev_packet_data = pr_size;
			DWORD recv_flag = 0;
			int ret = WSARecv(g_clients[ci].client_socket,
				&g_clients[ci].recv_over.wsabuf, 1,
				NULL, &recv_flag, &g_clients[ci].recv_over.over, NULL);

		boost::asio::async_read(g_clients[num_connections].client_socket, boost::asio::buffer(g_clients[num_connections].packet_buf, MAX_BUFFER),
			[](const boost::system::error_code& error, size_t bytes) {});
	}
	else
	{
		DisconnectClient(client_id);
		--num_connections;
	}
}

void OnConnect(const boost::system::error_code& error, const tcp::endpoint& endpoint)
{
	g_clients[num_connections].curr_packet_size = 0;
	g_clients[num_connections].prev_packet_data = 0;

	boost::asio::async_read(g_clients[num_connections].client_socket, boost::asio::buffer(g_clients[num_connections].packet_buf, MAX_BUFFER),
		[](const boost::system::error_code& error, size_t bytes) {});
}

void Adjust_Number_Of_Client()
{
	static int delay_multiplier = 1;
	static int max_limit = MAXINT;
	static bool increasing = true;

	if (active_clients >= MAX_TEST) return;
	if (num_connections >= MAX_CLIENTS) return;

	auto duration = high_resolution_clock::now() - last_connect_time;
	if (ACCEPT_DELY * delay_multiplier > duration_cast<milliseconds>(duration).count()) return;

	int t_delay = global_delay;
	if (DELAY_LIMIT2 < t_delay) 
	{
		if (true == increasing)
		{
			max_limit = active_clients;
			increasing = false;
		}
		if (100 > active_clients) return;
		if (ACCEPT_DELY * 10 > duration_cast<milliseconds>(duration).count()) return;
		last_connect_time = high_resolution_clock::now();
		DisconnectClient(client_to_close);
		client_to_close++;
		return;
	}
	else
	{
		if (DELAY_LIMIT < t_delay) 
		{
			delay_multiplier = 10;
			return;
		}
	}

	if (max_limit - (max_limit / 20) < active_clients) return;

	increasing = true;
	last_connect_time = high_resolution_clock::now();
	g_clients[num_connections].id = num_connections;
	g_clients[num_connections].client_socket = tcp::socket(g_context);

	g_resolver.async_resolve(g_query, [](const boost::system::error_code& error, tcp::resolver::results_type results)
		{
			if (!error)
				boost::asio::async_connect(g_clients[num_connections].client_socket, results, OnConnect);
		});

	num_connections++;
	return;
}

string GenerateRandomString()
{
	string s;
	s.resize(MAX_STR_LEN);

	for (int i = 0; i < MAX_STR_LEN; ++i)
		s[i] = rand();

	return s;
}

void Test_Thread()
{
	while (true) 
	{
		//Sleep(max(20, global_delay));
		Adjust_Number_Of_Client();

		for (int i = 0; i < num_connections; ++i)
		{
			if (false == g_clients[i].connected) continue;
			if (g_clients[i].last_move_time + 1s > high_resolution_clock::now()) continue;
			g_clients[i].last_move_time = high_resolution_clock::now();

			ChattingPacket packet;
			packet.message = GenerateRandomString();
			packet.header.type = static_cast<short>(ClientCommand::Chatting);
			packet.header.size = sizeof(Header) + packet.message.size();

			SendPacket(i, &packet);
		}
	}
}

void InitializeNetwork()
{
	for (auto& cl : g_clients) 
	{
		cl.connected = false;
		cl.id = INVALID_ID;
	}

	num_connections = 0;
	last_connect_time = high_resolution_clock::now();

	g_resolver = tcp::resolver(g_context);

	for (int i = 0; i < 6; ++i)
		worker_threads.push_back(new std::thread{ Worker_Thread });

	test_thread = thread{ Test_Thread };

	g_context.run();

}

void ShutdownNetwork()
{
	test_thread.join();
	for (auto pth : worker_threads)
	{
		pth->join();
		delete pth;
	}
}

void Do_Network()
{
	return;
}

void GetPointCloud(int* size, float** points)
{
	int index = 0;
	for (int i = 0; i < num_connections; ++i)
		if (true == g_clients[i].connected)
		{
			point_cloud[index * 2] = static_cast<float>(g_clients[i].x);
			point_cloud[index * 2 + 1] = static_cast<float>(g_clients[i].y);
			index++;
		}

	*size = index;
	*points = point_cloud;
}

