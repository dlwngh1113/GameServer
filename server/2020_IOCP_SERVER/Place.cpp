#include "stdafx.h"
#include "Place.h"
#include "User.h"
#include "Sector.h"

Sector* Place::GetSectorByPoint(short x, short y)
{
	//Sector* sector = nullptr;
	//for (int i = 0; i < m_nHeightSectorSize; ++i)
	//{
	//	for (int j = 0; j < m_nWidthSectorSize; ++j)
	//	{
	//		if (m_sectors[i][j].IsPointInSector(x, y))
	//			return &m_sectors[i][j];
	//	}
	//}

	//return nullptr;

	int nHeightIndex = x / m_nHeightSectorSize;
	int nWidthIndex = y / m_nWidthSectorSize;

	if (0 <= nHeightIndex && nHeightIndex < m_nHeightSectorSize)
		if (0 <= nWidthIndex && nWidthIndex < m_nWidthSectorSize)
			return &m_sectors[x / m_nWidthSectorSize][y / m_nHeightSectorSize];

	return nullptr;
}

Place::Place()
{
}

Place::Place(int nId, int nWidth, int nHeight, int nWidthSectorSize, int nHeightSectorSize) : m_nId{ nId }, m_nWidth { nWidth }, m_nHeight{ nHeight }, m_nWidthSectorSize{ nWidthSectorSize }, m_nHeightSectorSize{ nHeightSectorSize }
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
			m_sectors[i][j].Init(j * nSectorWidth, i* nSectorHeight, nSectorWidth, nSectorHeight);
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

void Place::SendEvent(const int nId, ClientCommon::BasePacket* ev)
{
	m_lock.lock();
	for (const auto& pair : m_users)
		if (pair.second->GetID() != nId)
			pair.second->SendPacket(ev);
	m_lock.unlock();
}

void Place::GetNearSectors(Sector* sector, std::unordered_set<Sector*>& sectors)
{
	int minX = sector->getX() - 1 < 0 ? 0 : sector->getX() - 1;
	int maxX = sector->getX() + 1 >= m_nWidthSectorSize  ? m_nWidthSectorSize - 1 : sector->getX() + 1;

	int minY = sector->getY() - 1 < 0 ? 0 : sector->getY() - 1;
	int maxY = sector->getY() + 1 >= m_nHeightSectorSize ? m_nHeightSectorSize : sector->getY() - 1;

	for (int i = minX; i < maxX; ++i)
		for (int j = minY; j < maxY; ++j)
			sectors.insert(&m_sectors[i][j]);
}

std::unique_ptr<SectorChangeInfo> Place::GetSectorChangeInfo(Sector* prevSector, Sector* currSector)
{
	std::unique_ptr<SectorChangeInfo> sectorChangeInfo = std::make_unique<SectorChangeInfo>();

	std::unordered_set<Sector*> prevNearSectors;
	std::unordered_set<Sector*> currNearSectors;

	// prevSector 포함 9개와 currSector 포함 9개를 가져온다
	GetNearSectors(prevSector, prevNearSectors);
	GetNearSectors(currSector, currNearSectors);

	for (const auto& s : prevNearSectors)
	{
		if (currNearSectors.count(s))
			sectorChangeInfo->notChangedSectors.insert(s);
		else
			sectorChangeInfo->exitedSectors.insert(s);
	}
	for (const auto& s : currNearSectors)
		if (!prevNearSectors.count(s))
			sectorChangeInfo->enteredSectors.insert(s);

	return std::move(sectorChangeInfo);
}

void Place::AddUser(std::shared_ptr<User> user)
{
	m_lock.lock();
	m_users.insert(std::make_pair(user->GetID(), user));
	m_lock.unlock();

	//
	// 이벤트 데이터 세팅
	//

	ClientCommon::UserEnterEvent ev;
	ev.header.size = sizeof(ev);
	ev.header.type = static_cast<short>(ServerEvent::UserEnter);
	ev.id = user->GetID();
	strcpy_s(ev.name, user->GetName());
	ev.x = user->GetX();
	ev.y = user->GetY();

	// 발송

	SendEvent(user->GetID(), &ev);
}

void Place::RemoveUser(const int nId)
{
	m_lock.lock();
	m_users.erase(nId);
	m_lock.unlock();

	//
	// 이벤트 데이터 세팅
	//

	ClientCommon::UserExitEvent ev;
	ev.header.size = sizeof(ev);
	ev.header.type = static_cast<short>(ServerEvent::UserExit);
	ev.id = nId;

	// 발송

	SendEvent(nId, &ev);
}

void Place::Move(std::shared_ptr<User> user, short x, short y)
{
	if (0 > x || m_nWidth < x)
		return;
	if (0 > y || m_nHeight < y)
		return;

	// 이동

	short currX{ user->GetX() }, currY{ user->GetY() };

	Sector* prevSector = GetSectorByPoint(currX, currY);
	Sector* currentSector = GetSectorByPoint(x, y);

	user->SetPosition(x, y);

	if (prevSector != currentSector)
	{
		auto sectorChangeInfo = GetSectorChangeInfo(prevSector, currentSector);

		for (const auto& s : sectorChangeInfo->enteredSectors)
			s->AddUser(user.get());
		for (const auto& s : sectorChangeInfo->exitedSectors)
			s->RemoveUser(user.get());
		for (const auto& s : sectorChangeInfo->notChangedSectors)
			s->Move(user.get());
	}
	else
	{
		std::unordered_set<Sector*> sectors;
		GetNearSectors(currentSector, sectors);

		for (const auto& s : sectors)
			s->Move(user.get());
	}
}