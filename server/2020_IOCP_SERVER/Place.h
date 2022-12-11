#pragma once
#include"User.h"

class Place
{
private:
	int m_nWidth{ 0 }, m_nHeight{ 0 }, m_nWidthSectorSize{ 0 }, m_nHeightSectorSize{ 0 };
	std::mutex m_lock;
	std::unordered_map<int, User*> m_users;

	//Sector** m_sectors = nullptr;
	//Sector* GetSectorByPoint(short x, short y);

	void SendUserEnterEvent(User* targetUser);
public:
	Place();
	Place(int nWidth, int nHeight, int nWidthSectorSize, int nHeightSectorSize);
	virtual ~Place();

	void AddUser(User* user);
	void Move(User* user, short x, short y);
};