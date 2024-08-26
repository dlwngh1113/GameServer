#include "stdafx.h"
#include "Sector.h"
#include "User.h"

Sector::Sector()
{
}

Sector::~Sector()
{
	m_users.clear();
}

void Sector::SendUserEnter(std::shared_ptr<User> targetUser)
{
	//// 이벤트 데이터 세팅

	//Common::UserEnterEvent ev;
	//ev.header.size = sizeof(ev);
	//ev.header.type = static_cast<short>(ServerEvent::UserEnter);
	//ev.id = targetUser->GetID();
	//strcpy_s(ev.name, targetUser->GetName());
	//ev.x = targetUser->GetX();
	//ev.y = targetUser->GetY();

	//// event 발송

	//for (const auto& user : m_users)
	//	if (targetUser != user)
	//		user->SendPacket(&ev);
}

void Sector::SendUserExit(std::shared_ptr<User> targetUser)
{
	//// 이벤트 데이터 세팅

	//Common::UserExitEvent ev;
	//ev.header.size = sizeof(ev);
	//ev.header.type = static_cast<short>(ServerEvent::UserExit);
	//ev.id = targetUser->GetID();

	//// 이벤트 발송

	//for (const auto& user : m_users)
	//	if (user != targetUser)
	//		user->SendPacket(&ev);
}

void Sector::Move(std::shared_ptr<User> targetUser)
{
	// 이벤트 데이터 세팅

	Common::MoveEventBody ev;
	ev.id = std::atoi(targetUser->userId().c_str());
	ev.userId = targetUser->userId();
	ev.x = targetUser->x();
	ev.y = targetUser->y();
	ev.moveTime = targetUser->moveTime();

	// 이벤트 발송

	for (const auto& user : m_users)
		user->SendPacket(&ev);
}

void Sector::AddUser(std::shared_ptr<User> user)
{
	if (m_users.count(user) > 0)
		return;

	m_lock.lock();
	m_users.insert(user);
	m_lock.unlock();

	//
	// �̺�Ʈ �߼�
	//

	//for (const auto& u : m_users)
	//{
	//	Common::UserEnterEvent ev;
	//	ev.header.size = sizeof(ev);
	//	ev.header.type = static_cast<short>(ServerEvent::UserEnter);
	//	ev.id = u->GetID();
	//	strcpy_s(ev.name, u->GetName());
	//	ev.x = u->GetX();
	//	ev.y = u->GetY();

	//	user->SendPacket(&ev);
	//}

	//SendUserEnter(user);
}

void Sector::RemoveUser(std::shared_ptr<User> user)
{
	if (m_users.count(user) == 0)
		return;

	m_lock.lock();
	m_users.erase(user);
	m_lock.unlock();

	////
	//// �̺�Ʈ �߼�
	////

	//for (const auto& u : m_users)
	//{
	//	Common::UserExitEvent ev;
	//	ev.header.size = sizeof(ev);
	//	ev.header.type = static_cast<short>(ServerEvent::UserExit);
	//	ev.id = u->GetID();

	//	user->SendPacket(&ev);
	//}

	//SendUserExit(user);
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