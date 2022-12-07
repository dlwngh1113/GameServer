#include "stdafx.h"
#include "Sector.h"

Sector::Sector()
{
}

Sector::~Sector()
{
	m_users.clear();
}

void Sector::AddUser(User* user)
{
	m_lock.lock();
	m_users.insert(user);
	user->ChangeSector(this);
	m_lock.unlock();

	//
	// 이벤트 발송
	//

	for (const auto& user : m_users)
	{
		UserEnterEvent ev;
		ev.type = 
		user->SendPacket()
	}
}

Sector* Sector::RemoveUser(User* user)
{
	if (m_users.count(user) != 0)
	{
		m_lock.lock();
		m_users.erase(user);
		user->ChangeSector(nullptr);
		m_lock.unlock();

		//
		// 이벤트 발송
		//



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
