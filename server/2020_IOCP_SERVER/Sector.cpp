#include "stdafx.h"
#include "Sector.h"

Sector::Sector(int nX, int nY, int nWidth, int nHeight) : m_nX{ nX }, m_nY{ nY }, m_nWidth{ nWidth }, m_nHeight{ nHeight }
{
}

Sector::~Sector()
{
	m_users.clear();
}

void Sector::AddUser(User* user)
{
	m_users.insert(user);
}

void Sector::RemoveUser(User* user)
{
	if (m_users.count(user) != 0)
		m_users.erase(user);
}
