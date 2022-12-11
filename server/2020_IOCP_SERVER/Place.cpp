#include "stdafx.h"
#include "Place.h"

//Sector* Place::GetSectorByPoint(short x, short y)
//{
//	Sector* sector = nullptr;
//	for (int i = 0; i < m_nHeightSectorSize; ++i)
//	{
//		for (int j = 0; j < m_nWidthSectorSize; ++j)
//		{
//			if (m_sectors[i][j].IsPointInSector(x, y))
//				return &m_sectors[i][j];
//		}
//	}
//
//	return nullptr;
//}

Place::Place()
{
}

Place::Place(int nWidth, int nHeight, int nWidthSectorSize, int nHeightSectorSize) : m_nWidth{ nWidth }, m_nHeight{ nHeight }, m_nWidthSectorSize{ nWidthSectorSize }, m_nHeightSectorSize{ nHeightSectorSize }
{
	//// 각 섹터별 너비, 높이
	//int nSectorWidth = m_nWidth / m_nWidthSectorSize;
	//int nSectorHeight = m_nHeight / m_nHeightSectorSize;

	//// 섹터 할당
	//m_sectors = new Sector * [m_nHeightSectorSize];
	//for (int i = 0; i < m_nHeightSectorSize; ++i)
	//{
	//	m_sectors[i] = new Sector[m_nWidthSectorSize];
	//	for (int j = 0; j < m_nWidthSectorSize; ++j)
	//	{
	//		m_sectors[i][j].Init(j * nSectorWidth, i* nSectorHeight, nSectorWidth, nSectorHeight);
	//	}
	//}
}

Place::~Place()
{
	//for (int i = 0; i < m_nHeightSectorSize; ++i)
	//	if (m_sectors[i])
	//		delete[] m_sectors[i];

	//if (m_sectors)
	//	delete[] m_sectors;
}

void Place::RemoveUser(User* user)
{
	m_lock.lock();
	m_users.erase(user->GetID());
	m_lock.unlock();

	//
	// 이벤트 발송
	//

	SendUserExitEvent(user);
}

void Place::SendUserExitEvent(User* targetUser)
{
	// 이벤트 데이터 세팅

	UserExitEvent ev;
	ev.size = sizeof(ev);
	ev.type = SC_PACKET_EXIT;
	ev.id = targetUser->GetID();

	// 발송

	m_lock.lock();
	for (const auto& pair : m_users)
		if (pair.second != targetUser)
			pair.second->SendPacket(&ev);
	m_lock.unlock();
}

void Place::AddUser(User* user)
{
	m_lock.lock();
	m_users.insert(std::make_pair(user->GetID(), user));
	m_lock.unlock();

	//
	// 이벤트 발송
	//

	SendUserEnterEvent(user);
}

void Place::SendUserEnterEvent(User* targetUser)
{
	// 이벤트 데이터 세팅

	UserEnterEvent ev;
	ev.size = sizeof(ev);
	ev.type = SC_PACKET_ENTER;
	ev.id = targetUser->GetID();
	strcpy_s(ev.name, targetUser->GetName());
	ev.x = targetUser->GetX();
	ev.y = targetUser->GetY();

	// 발송

	m_lock.lock();
	for (const auto& pair : m_users)
		if (pair.second != targetUser)
			pair.second->SendPacket(&ev);
	m_lock.unlock();
}

void Place::Move(User* user, short x, short y)
{
	if (0 > x || m_nWidth < x)
		return;
	if (0 > y || m_nHeight < y)
		return;

	// 이동

	user->SetPosition(x, y);

	// 이벤트 발송

	SendUserMoveEvent(user);
}

void Place::SendUserMoveEvent(User* targetUser)
{
	// 이벤트 데이터 세팅

	UserMoveEvent ev;
	ev.size = sizeof(ev);
	ev.type = SC_PACKET_MOVE;
	ev.id = targetUser->GetID();
	ev.x = targetUser->GetX();
	ev.y = targetUser->GetY();

	// 발송

	m_lock.lock();
	for (const auto& pair : m_users)
		if (pair.second != targetUser)
			pair.second->SendPacket(&ev);
	m_lock.unlock();
}