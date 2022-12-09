#include "stdafx.h"
#include "Place.h"

Sector* Place::GetSectorByPoint(short x, short y)
{
	Sector* sector = nullptr;
	for (int i = 0; i < m_nHeightSectorSize; ++i)
	{
		for (int j = 0; j < m_nWidthSectorSize; ++j)
		{
			if (m_sectors[i][j].IsPointInSector(x, y))
				return &m_sectors[i][j];
		}
	}

	return nullptr;
}

Place::Place()
{
}

Place::Place(int nWidth, int nHeight, int nWidthSectorSize, int nHeightSectorSize) : m_nWidth{ nWidth }, m_nHeight{ nHeight }, m_nWidthSectorSize{ nWidthSectorSize }, m_nHeightSectorSize{ nHeightSectorSize }
{
	// 각 섹터별 너비, 높이
	int nSectorWidth = m_nWidth / m_nWidthSectorSize;
	int nSectorHeight = m_nHeight / m_nHeightSectorSize;

	// 섹터 할당
	m_sectors = new Sector * [m_nHeightSectorSize];
	for (int i = 0; i < m_nHeightSectorSize; ++i)
	{
		m_sectors[i] = new Sector[m_nWidthSectorSize];
		for (int j = 0; j < m_nWidthSectorSize; ++j)
		{
			m_sectors[i][j].Init(i* nSectorWidth, j* nSectorHeight, nSectorWidth, nSectorHeight);
		}
	}
}

Place::~Place()
{
	for (int i = 0; i < m_nHeightSectorSize; ++i)
		if (m_sectors[i])
			delete[] m_sectors[i];

	if (m_sectors)
		delete[] m_sectors;
}

void Place::AddUser(User* user)
{
	Sector* sector = GetSectorByPoint(user->GetX(), user->GetY());
	user->ChangeSector(sector);
}

void Place::Move(User* user, short x, short y)
{
	Sector* targetSector = GetSectorByPoint(x, y);
	if (targetSector == nullptr)
	{
		Logger::Error("좌표가  범위를 벗어납니다. x = " + std::to_string(x) + ", y = " + std::to_string(y));
		return;
	}

	if (user->GetSector() != targetSector)
	{
		user->GetSector()->RemoveUser(user);
		user->ChangeSector(targetSector);
	}

	user->Move(x, y);
}
