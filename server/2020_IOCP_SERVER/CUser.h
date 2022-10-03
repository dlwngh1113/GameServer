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
public:
	UserState GetUserState() const;
};

