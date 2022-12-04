#pragma once
#include"Sector.h"

class Place
{
private:
	const int nWidth = 10;
	const int nHeight = 10;
	Sector** m_sectors;

public:
	Place();
	virtual ~Place();
};

