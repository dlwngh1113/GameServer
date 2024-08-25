#pragma once
#include "Singleton.h"
#include "Sector.h"

struct SectorChangeInfo;

class Place : public Core::Singleton<Place>
{
private:
	int m_nId{ 0 };
	int m_nWidth{ 0 }, m_nHeight{ 0 }, m_nWidthSectorSize{ 0 }, m_nHeightSectorSize{ 0 };
	std::mutex m_lock;
	std::unordered_set<std::shared_ptr<User>> m_users;

	Sector** m_sectors = nullptr;
	Sector* GetSectorByPoint(int x, int y);

	void SendEvent(const boost::uuids::uuid& id, Common::Packet* packet);
	void GetNearSectors(Sector* sector, std::unordered_set<Sector*>& sectors);
	std::unique_ptr<SectorChangeInfo> GetSectorChangeInfo(Sector* prevSector, Sector* currSector);
public:
	Place();
	explicit Place(int nId, int nWidth, int nHeight, int nWidthSectorSize, int nHeightSectorSize);
	virtual ~Place();

	int GetId() const { return m_nId; }

	void AddUser(std::shared_ptr<User> user);
	void RemoveUser(std::shared_ptr<User> user);
	void Move(std::shared_ptr<User> user, int x, int y);
};
