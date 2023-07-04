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

void Sector::Init(int nX, int nY, int nWidth, int nHeight)
{
	m_nX = nX;
	m_nY = nY;
	m_nWidth = nWidth;
	m_nHeight = nHeight;
}

void Sector::SendEvent(const std::unordered_set<User*>& users, User* userToExclude, ClientCommon::BasePacket* ev)
{
	for (const auto& user : users)
		if (userToExclude != user)
			user->SendPacket(ev);
}

void Sector::SendUserEnter(const std::unordered_set<User*>& users, User* targetUser)
{
	// event 데이터 세팅

	ClientCommon::UserEnterEvent ev;
	ev.header.size = sizeof(ev);
	ev.header.type = static_cast<short>(ServerEvent::UserEnter);
	ev.id = targetUser->GetID();
	strcpy_s(ev.name, targetUser->GetName());
	ev.x = targetUser->GetX();
	ev.y = targetUser->GetY();

	// 이벤트 발송

	SendEvent(users, targetUser, &ev);
}

void Sector::SendUserExit(const std::unordered_set<User*>& users, User* targetUser)
{
	// event 데이터 세팅

	ClientCommon::UserExitEvent ev;
	ev.header.size = sizeof(ev);
	ev.header.type = static_cast<short>(ServerEvent::UserExit);
	ev.id = targetUser->GetID();

	// 이벤트 발송

	SendEvent(users, targetUser, &ev);
}

void Sector::Move(User* targetUser)
{
	std::unique_lock<std::mutex> lock{ m_lock };
	std::unordered_set<User*> users{ m_users };
	lock.unlock();

	// event 데이터 세팅

	ClientCommon::UserMoveEvent ev;
	ev.header.size = sizeof(ev);
	ev.header.type = static_cast<short>(ServerEvent::UserMove);
	ev.id = targetUser->GetID();
	ev.x = targetUser->GetX();
	ev.y = targetUser->GetY();

	// 이벤트 발송

	SendEvent(users, targetUser, &ev);
}

void Sector::AddUser(User* user)
{
	std::unique_lock<std::mutex> lock{ m_lock };
	m_users.insert(user);
	std::unordered_set<User*> users = m_users;
	lock.unlock();

	//
	// 이벤트 발송
	//

	for (const auto& u : users)
	{
		ClientCommon::UserEnterEvent ev;
		ev.header.size = sizeof(ev);
		ev.header.type = static_cast<short>(ServerEvent::UserEnter);
		ev.id = u->GetID();
		strcpy_s(ev.name, u->GetName());
		ev.x = u->GetX();
		ev.y = u->GetY();

		user->SendPacket(&ev);
	}

	SendUserEnter(users, user);
}

void Sector::RemoveUser(User* user)
{
	if (m_users.size() <= 0)
		return;

	std::unique_lock<std::mutex> lock{ m_lock };
	m_users.erase(user);
	std::unordered_set<User*> users = m_users;
	lock.unlock();

	//
	// 이벤트 발송
	//

	for (const auto& u : users)
	{
		ClientCommon::UserExitEvent ev;
		ev.header.size = sizeof(ev);
		ev.header.type = static_cast<short>(ServerEvent::UserExit);
		ev.id = u->GetID();

		user->SendPacket(&ev);
	}

	SendUserExit(users, user);
}
