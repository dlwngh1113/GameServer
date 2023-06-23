#pragma once

#include "SectorChangeInfo.h"

struct BasePacket;
class User;

class Place
{
private:
	int m_nId{ 0 };
	int m_nWidth{ 0 }, m_nHeight{ 0 }, m_nWidthSectorSize{ 0 }, m_nHeightSectorSize{ 0 };
	std::mutex m_lock;
	std::unordered_map<int, std::shared_ptr<User>> m_users;

	Sector** m_sectors = nullptr;
	Sector* GetSectorByPoint(short x, short y);

	void SendEvent(const int nId, ClientCommon::BasePacket* packet);
	void GetNearSectors(Sector* sector, std::unordered_set<Sector*>& sectors);
	std::unique_ptr<SectorChangeInfo> GetSectorChangeInfo(Sector* prevSector, Sector* currSector);
public:
	Place();
	explicit Place(int nId, int nWidth, int nHeight, int nWidthSectorSize, int nHeightSectorSize);
	virtual ~Place();

	int GetId() const { return m_nId; }

	void AddUser(std::shared_ptr<User> user);
	void RemoveUser(const int nId);
	void Move(std::shared_ptr<User> user, short x, short y);
};