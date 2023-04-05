#pragma once

struct BasePacket;
class User;
class Sector;

class Place
{
private:
	int m_nWidth{ 0 }, m_nHeight{ 0 }, m_nWidthSectorSize{ 0 }, m_nHeightSectorSize{ 0 };
	std::mutex m_lock;
	std::unordered_map<int, std::shared_ptr<User>> m_users;

	Sector** m_sectors = nullptr;
	Sector* GetSectorByPoint(short x, short y);

	void SendEvent(const std::shared_ptr<User>& userToExclude, BasePacket* packet);
public:
	Place();
	Place(int nWidth, int nHeight, int nWidthSectorSize, int nHeightSectorSize);
	virtual ~Place();

	void AddUser(std::shared_ptr<User> user);
	void RemoveUser(std::shared_ptr<User> user);
	void Move(std::shared_ptr<User> user, short x, short y);
};