#pragma once
#include"framework.h"

class CClient
{
	std::mutex c_lock;
	char name[MAX_ID_LEN];
	short level;
	short hp;
	short x, y;
	int exp;
	lua_State* L;
	std::mutex lua_l;

	bool in_use;
	std::atomic_bool is_active;
	SOCKET	m_sock;
	OVER_EX	m_recv_over;
	unsigned char* m_packet_start;
	unsigned char* m_recv_start;

	std::mutex vl;
	std::unordered_set <int> view_list;

	int move_time;
	int atk_time;

	void send_packet(void* p);
public:
#pragma region getter
	short getHP() const;
	bool getUse() const;
#pragma endregion

#pragma region setter
	void SetUse(bool b);
	void SetClient(SOCKET ns);
#pragma endregion
	void Init(short x, short y, short level, char* name, int i);
	void Release();

	void MoveNotify(int objID);
	void AutoHeal();
	void send_heal_packet(char* mess);
	void send_leave_packet(int targetID);
	void StartRecv();
};