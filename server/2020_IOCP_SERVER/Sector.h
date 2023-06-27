#pragma once

class User;

class Sector
{
private:
	int m_nX{ 0 }, m_nY{ 0 }, m_nWidth{ 0 }, m_nHeight{ 0 };
	std::unordered_set<User*> m_users;
	std::mutex m_lock;

	void SendUserEnter(User* user);
	void SendUserExit(User* targetUser);

public:
	Sector();
	virtual ~Sector();
	void Init(int nX, int nY, int nWidth, int nHeight);

	int getX() const { return m_nX / m_nWidth; }
	int getY() const { return m_nY / m_nHeight; }

	void Move(User* targetUser);
	void AddUser(User* user);
	void RemoveUser(User* user);
};