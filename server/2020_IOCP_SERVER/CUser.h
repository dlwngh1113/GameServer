#pragma once
#include"framework.h"

enum class UserState {
	LOGINBEGIN,
	LOGGINGIN,
	LOGGEDIN
};

class CUser
{
	UserState m_userState;
	SOCKET m_sock;
	OVER_EX m_recv_over;
	std::mutex m_ioLock;
public:
	UserState GetUserState() const;
	void InitIO();
};

