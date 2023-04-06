#include "stdafx.h"
#include "Sector.h"
#include"User.h"

Sector::Sector()
{
}

Sector::~Sector()
{
	m_users.clear();
}

void Sector::SendUserEnter(User* targetUser)
{
	for (const auto& user : m_users)
	{
		if (targetUser != user)
		{
			ClientCommon::UserEnterEvent ev;
			ev.size = sizeof(ev);
			ev.type = ClientCommon::SC_PACKET_ENTER;
			ev.id = targetUser->GetID();
			strcpy_s(ev.name, targetUser->GetName());
			ev.x = targetUser->GetX();
			ev.y = targetUser->GetY();

			user->SendPacket(&ev);
		}
	}
}

void Sector::SendUserExit(User* targetUser)
{
	for (const auto& user : m_users)
	{
		if (user != targetUser)
		{
			ClientCommon::UserExitEvent ev;
			ev.size = sizeof(ev);
			ev.type = ClientCommon::SC_PACKET_EXIT;
			ev.id = targetUser->GetID();

			user->SendPacket(&ev);
		}
	}
}

void Sector::Move(User* targetUser)
{
	for (const auto& user : m_users)
	{
		if (user != targetUser)
		{
			ClientCommon::UserMoveEvent ev;
			ev.size = sizeof(ev);
			ev.type = ClientCommon::SC_PACKET_MOVE;
			ev.id = targetUser->GetID();
			ev.x = targetUser->GetX();
			ev.y = targetUser->GetY();

			user->SendPacket(&ev);
		}
	}
}

void Sector::AddUser(User* user)
{
	m_lock.lock();
	m_users.insert(user);
	m_lock.unlock();

	//
	// 이벤트 발송
	//

	for (const auto& u : m_users)
	{
		ClientCommon::UserEnterEvent ev;
		ev.size = sizeof(ev);
		ev.type = ClientCommon::SC_PACKET_ENTER;
		ev.id = u->GetID();
		strcpy_s(ev.name, u->GetName());
		ev.x = u->GetX();
		ev.y = u->GetY();

		user->SendPacket(&ev);
	}
	SendUserEnter(user);
}

Sector* Sector::RemoveUser(User* user)
{
	if (m_users.count(user) != 0)
	{
		m_lock.lock();
		m_users.erase(user);
		m_lock.unlock();

		//
		// 이벤트 발송
		//

		SendUserExit(user);

		return this;
	}
}

void Sector::Init(int nX, int nY, int nWidth, int nHeight)
{
	m_nX = nX;
	m_nY = nY;
	m_nWidth = nWidth;
	m_nHeight = nHeight;
}

bool Sector::IsPointInSector(short x, short y)
{
	return (((m_nX < x) && (x <= m_nX + m_nWidth)) && ((m_nY < y) && (y <= m_nY + m_nHeight)));
}
