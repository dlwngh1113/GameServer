#pragma once
#include"Sector.h"

class Place
{
private:
	int m_nWidth{ 0 }, m_nHeight{ 0 }, m_nWidthSectorSize{ 0 }, m_nHeightSectorSize{ 0 };
	Sector** m_sectors = nullptr;

public:
	Place();
	Place(int nWidth, int nHeight, int nWidthSectorSize, int nHeightSectorSize);
	virtual ~Place();
};