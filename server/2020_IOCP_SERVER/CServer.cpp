#include "CServer.h"

CServer::CServer()
{
	timer = new CTimer();
	npcController = new CNPCController();
	dbConnector = new CDBConnector();
}

CServer::~CServer()
{
	delete timer;
	delete npcController;
	delete dbConnector;
}

void CServer::run()
{
	std::wcout.imbue(std::locale("korean"));

	dbConnector->Init();

	WSADATA WSAData;
	WSAStartup(MAKEWORD(2, 0), &WSAData);
	h_iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 0);
	g_lSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	CreateIoCompletionPort(reinterpret_cast<HANDLE>(g_lSocket), h_iocp, KEY_SERVER, 0);

	SOCKADDR_IN serverAddr;
	memset(&serverAddr, 0, sizeof(SOCKADDR_IN));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	::bind(g_lSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
	listen(g_lSocket, 5);

	SOCKET cSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	g_accept_over.op_mode = OP_MODE_ACCEPT;
	g_accept_over.wsa_buf.len = static_cast<int>(cSocket);
	ZeroMemory(&g_accept_over.wsa_over, sizeof(&g_accept_over.wsa_over));
	AcceptEx(g_lSocket, cSocket, g_accept_over.iocp_buf, 0, 32, 32, NULL, &g_accept_over.wsa_over);

	initialize_NPC();

	//thread ai_thread{ npc_ai_thread };
	timer = new CTimer;
	std::vector <std::thread> worker_threads;
	for (int i = 0; i < 4; ++i)
		worker_threads.emplace_back(&worker_thread);
	for (auto& th : worker_threads)
		th.join();
	//ai_thread.join();
	timer->join();

	dbConnector->Release();
	closesocket(g_lSocket);
	WSACleanup();
}

void CServer::initialize_NPC()
{
	std::cout << "Initializing NPCs\n";
	for (int i = MAX_USER; i < MAX_USER + NUM_NPC; ++i)
	{
		char npc_name[50];
		sprintf_s(npc_name, "N%d", i);

		g_clients[i].Init(rand() % WORLD_WIDTH,
						rand() % WORLD_HEIGHT,
						rand() % 10 + 1,
						npc_name, i);

		lua_register(g_clients[i].getLua(), "API_SendEnterMessage", API_SendEnterMessage);
		lua_register(g_clients[i].getLua(), "API_SendLeaveMessage", API_SendLeaveMessage);
		lua_register(g_clients[i].getLua(), "API_get_x", API_get_x);
		lua_register(g_clients[i].getLua(), "API_get_y", API_get_y);
	}
	std::cout << "NPC initialize finished.\n";
}

void CServer::worker_thread()
{
	// �ݺ�
	//   - �� �����带 IOCP thread pool�� ���  => GQCS
	//   - iocp�� ó���� �±� I/O�Ϸ� �����͸� ������ => GQCS
	//   - ���� I/O�Ϸ� �����͸� ó��
	while (true) {
		DWORD io_size;
		int key;
		ULONG_PTR iocp_key;
		WSAOVERLAPPED* lpover;
		//int ret = 
		GetQueuedCompletionStatus(h_iocp, &io_size, &iocp_key, &lpover, INFINITE);
		key = static_cast<int>(iocp_key);
		// cout << "Completion Detected" << endl;
		//if (FALSE == ret) {
		//	error_display("GQCS Error : ", WSAGetLastError());
		//}

		OVER_EX* over_ex = reinterpret_cast<OVER_EX*>(lpover);
		switch (over_ex->op_mode) {
		case OP_MODE_ACCEPT:
			add_new_client(static_cast<SOCKET>(over_ex->wsa_buf.len));
			break;
		case OP_MODE_RECV:
			if (0 == io_size)
				disconnect_client(key);
			else {
				// cout << "Packet from Client [" << key << "]" << endl;
				process_recv(key, io_size);
			}
			break;
		case OP_MODE_SEND:
			delete over_ex;
			break;
		case OP_RANDOM_MOVE:
			if (reinterpret_cast<CClient*>(characters[key])->getHP() > 0)
				npcController->random_move_npc(key);
			delete over_ex;
			break;
		case OP_PLAYER_MOVE_NOTIFY:
			g_clients[key].MoveNotify(over_ex->object_id);
			delete over_ex;
			break;
		case OP_HEAL:
		{
			timer->add_timer(key, OP_HEAL, std::chrono::system_clock::now() + std::chrono::seconds(5));
			delete over_ex;
		}
			break;
		}
	}
}

void CServer::add_new_client(SOCKET ns)
{
	int i;
	id_lock.lock();
	for (i = 0; i < MAX_USER; ++i)
		if (false == g_clients[i].getUse()) break;
	id_lock.unlock();
	if (MAX_USER == i) {
		std::cout << "Max user limit exceeded.\n";
		closesocket(ns);
	}
	else {
		// cout << "New Client [" << i << "] Accepted" << endl;
		g_clients[i].SetClient(i, ns);
		CreateIoCompletionPort(reinterpret_cast<HANDLE>(ns), h_iocp, i, 0);
		g_clients[i].StartRecv();
		timer->add_timer(i, OP_HEAL, std::chrono::system_clock::now() + std::chrono::seconds(5));
	}

	SOCKET cSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	g_accept_over.op_mode = OP_MODE_ACCEPT;
	g_accept_over.wsa_buf.len = static_cast<ULONG> (cSocket);
	ZeroMemory(&g_accept_over.wsa_over, sizeof(&g_accept_over.wsa_over));
	AcceptEx(g_lSocket, cSocket, g_accept_over.iocp_buf, 0, 32, 32, NULL, &g_accept_over.wsa_over);
}

void CServer::disconnect_client(int id)
{
	for (auto& i : g_clients[id].getViewList())
		g_clients[i].ErasePlayer(id);
	dbConnector->set_userdata(&g_clients[id], false);
	g_clients[id].Release();
}

void CServer::wake_up_npc(int id)
{
	bool b = false;
	if (true == g_clients[id].CompareExchangeStrong(b))
	{
		timer->add_timer(id, OP_RANDOM_MOVE, std::chrono::system_clock::now() + std::chrono::seconds(1));
	}
}

bool CServer::is_near(int p1, int p2)
{
	int dist = (g_clients[p1].getX() - g_clients[p2].getX()) * (g_clients[p1].getX() - g_clients[p2].getX());
	dist += (g_clients[p1].getY() - g_clients[p2].getY()) * (g_clients[p1].getY() - g_clients[p2].getY());

	return dist <= VIEW_LIMIT * VIEW_LIMIT;
}

bool CServer::is_npc(int id)
{
	return id >= MAX_USER;
}

bool CServer::isIn_atkRange(int p1, int p2)
{
	int dist = (g_clients[p1].getX() - g_clients[p2].getX()) * (g_clients[p1].getX() - g_clients[p2].getX());
	dist += (g_clients[p1].getY() - g_clients[p2].getY()) * (g_clients[p1].getY() - g_clients[p2].getY());

	return dist <= 1;
}

void CServer::process_recv(int id, DWORD iosize)
{
	unsigned char* packet_start = g_clients[id].getPacketStart();
	unsigned char* next_recv_ptr = g_clients[id].getRecvStart() + iosize;
	unsigned char p_size = packet_start[0];
	while (p_size <= next_recv_ptr - packet_start) {
		process_packet(id);
		packet_start += p_size;
		if (packet_start < next_recv_ptr)
			p_size = packet_start[0];
		else break;
	}

	long long left_data = next_recv_ptr - packet_start;

	g_clients[id].IncreaseBuffer(iosize, left_data);
}

void CServer::process_packet(int id)
{
	char p_type = g_clients[id].getPacketType();
	switch (p_type) {
	case CS_LOGIN:
	{
		cs_packet_login* p = reinterpret_cast<cs_packet_login*>(g_clients[id].getPacketStart());
		process_login(p, id);
		break;
	}
	case CS_MOVE: {
		cs_packet_move* p = reinterpret_cast<cs_packet_move*>(g_clients[id].getPacketStart());
		if (g_clients[id].getMoveTime() < p->move_time) {
			g_clients[id].getMoveTime() = p->move_time;
			process_move(id, p->direction);
		}
	}
				break;
	case CS_LOGOUT:
	{
		disconnect_client(id);
	}
	break;
	case CS_ATTACK:
	{
		cs_packet_attack* p = reinterpret_cast<cs_packet_attack*>(g_clients[id].getPacketStart());
		if (g_clients[id].getAtktime() < p->atk_time) {
			g_clients[id].getAtktime() = p->atk_time;
			process_attack(id);
		}
	}
	break;
	case CS_TELEPORT:
	{
		cs_packet_teleport* p = reinterpret_cast<cs_packet_teleport*>(g_clients[id].getPacketStart());
		g_clients[id].SetPosition(p->x, p->y);
	}
	break;
	default: std::cout << "Unknown Packet type [" << p_type << "] from Client [" << id << "]\n";
		while (true);
	}
}

void CServer::process_login(cs_packet_login* p, int id)
{
	strcpy_s(g_clients[id].getName(), MAX_ID_LEN, p->name);
	for (int i = 0; i < MAX_USER; ++i) {
		if (g_clients[i].getUse() && (i != id))
			if (strcmp(g_clients[i].getName(), g_clients[id].getName()) != 0);
			else {
				g_clients[id].send_login_fail();
				return;
			}
	}
	dbConnector->set_userdata(&g_clients[id], true);

	if (dbConnector->GetReturnCode() != SQL_SUCCESS && dbConnector->GetReturnCode() != SQL_SUCCESS_WITH_INFO)
		dbConnector->get_userdata(&g_clients[id], p);

	g_clients[id].send_login_ok();
	for (int i = 0; i < MAX_USER; ++i)
		if (true == g_clients[i].getUse())
			if (id != i) {
				if (false == is_near(i, id)) continue;
				if (0 == g_clients[i].getViewList().count(id))
					g_clients[i].EnterPlayer(g_clients[id]);
				if (0 == g_clients[id].getViewList().count(i))
					g_clients[id].EnterPlayer(g_clients[i]);
			}
	for (int i = MAX_USER; i < MAX_USER + NUM_NPC; ++i) {
		if (false == is_near(id, i)) continue;
		g_clients[id].EnterPlayer(g_clients[i]);
		wake_up_npc(i);
	}
}

void CServer::process_move(int id, char dir)
{
	short y = g_clients[id].getY();
	short x = g_clients[id].getX();
	switch (dir) {
	case MV_UP: if (y > 0) y--; break;
	case MV_DOWN: if (y < (WORLD_HEIGHT - 1)) y++; break;
	case MV_LEFT: if (x > 0) x--; break;
	case MV_RIGHT: if (x < (WORLD_WIDTH - 1)) x++; break;
	default: std::cout << "Unknown Direction in CS_MOVE packet.\n";
		while (true);
	}
	std::unordered_set <int> old_viewlist = g_clients[id].getViewList();

	g_clients[id].SetPosition(x, y);
	g_clients[id].send_move_packet(g_clients[id]);

	std::unordered_set <int> new_viewlist;
	for (int i = 0; i < MAX_USER; ++i) {
		if (id == i) continue;
		if (false == g_clients[i].getUse()) continue;
		if (true == is_near(id, i)) new_viewlist.insert(i);
	}

	for (int i = MAX_USER; i < MAX_USER + NUM_NPC; ++i) {
		if (true == is_near(id, i)) {
			new_viewlist.insert(i);
			wake_up_npc(i);
		}
	}

	// �þ߿� ���� ��ü ó��
	for (int ob : new_viewlist) {
		if (0 == old_viewlist.count(ob)) {
			g_clients[id].EnterPlayer(g_clients[ob]);

			if (false == is_npc(ob)) {
				if (0 == g_clients[ob].getViewList().count(id)) {
					g_clients[ob].EnterPlayer(g_clients[id]);
				}
				else {
					g_clients[ob].send_move_packet(g_clients[id]);
				}
			}
		}
		else {  // �������� �þ߿� �־���, �̵��Ŀ��� �þ߿� �ִ� ��ü
			if (false == is_npc(ob)) {
				if (0 != g_clients[ob].getViewList().count(id)) {
					g_clients[ob].send_move_packet(g_clients[id]);
				}
				else
				{
					g_clients[ob].EnterPlayer(g_clients[id]);
				}
			}
		}
	}
	for (int ob : old_viewlist) {
		if (0 == new_viewlist.count(ob)) {
			g_clients[id].ErasePlayer(ob);
			if (false == is_npc(ob)) {
				if (0 != g_clients[ob].getViewList().count(id)) {
					g_clients[ob].ErasePlayer(id);
				}
			}
		}
	}

	if (false == is_npc(id)) {
		for (auto& npc : new_viewlist) {
			if (false == is_npc(npc)) continue;
			OVER_EX* ex_over = new OVER_EX;
			ex_over->object_id = id;
			ex_over->op_mode = OP_PLAYER_MOVE_NOTIFY;
			PostQueuedCompletionStatus(h_iocp, 1, npc, &ex_over->wsa_over);
		}
	}
}

void CServer::process_attack(int id)
{
	for (auto& i : g_clients[id].getViewList())
		if (isIn_atkRange(id, i)) {
			if (is_npc(i)) {
				char mess[MAX_STR_LEN];
				g_clients[i].HitByPlayer(mess);
				g_clients[id].send_chat_packet(id, mess);

				if (g_clients[i].getHP() <= 0) {
					timer->add_timer(i, OP_REVIVAL, std::chrono::system_clock::now() + std::chrono::seconds(30));
					sprintf_s(mess, "%s has dead, %d exp gain",
						g_clients[i].getName(), g_clients[i].getLevel() * 10);
				}
			}
		}
}

int CServer::API_get_x(lua_State* L)
{
	int user_id = lua_tointeger(L, -1);
	lua_pop(L, 2);
	int x = g_clients[user_id].getX();
	lua_pushnumber(L, x);
	return 1;
}

int CServer::API_get_y(lua_State* L)
{
	int user_id = lua_tointeger(L, -1);
	lua_pop(L, 2);
	int y = g_clients[user_id].getY();
	lua_pushnumber(L, y);
	return 1;
}

int CServer::API_SendEnterMessage(lua_State* L)
{
	int my_id = (int)lua_tointeger(L, -3);
	int user_id = (int)lua_tointeger(L, -2);
	char* mess = (char*)lua_tostring(L, -1);

	lua_pop(L, 3);

	if (std::chrono::system_clock::now().time_since_epoch().count() > g_clients[my_id].getAtktime())
	{
		g_clients[my_id].getAtktime() = std::chrono::system_clock::now().time_since_epoch().count();
		g_clients[user_id].hp -= 10;

		if (g_clients[user_id].getHP() <= 0) {
			g_clients[user_id].SetInfo(g_clients[user_id].getName(),
				g_clients[user_id].getLevel(),
				0, 0, g_clients[user_id].getExp() / 2,
				g_clients[user_id].getLevel() * 70);
		}

		g_clients[user_id].send_stat_change();
		char tmp[MAX_STR_LEN];
		sprintf_s(tmp, "You hit by id - %s", g_clients[my_id].getName());
		g_clients[user_id].send_chat_packet(user_id, tmp);
	}

	g_clients[user_id].send_chat_packet(my_id, mess);
	return 0;
}

int CServer::API_SendLeaveMessage(lua_State* L)
{
	int my_id = (int)lua_tointeger(L, -3);
	int user_id = (int)lua_tointeger(L, -2);
	char* mess = (char*)lua_tostring(L, -1);

	lua_pop(L, 3);

	timer->add_timer(my_id, OP_RUNAWAY, std::chrono::system_clock::now() + std::chrono::seconds(3), user_id, mess);

	return 0;
}
