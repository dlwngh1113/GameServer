#pragma once
#include "Singleton.h"
#include "Sector.h"

class Place : public Core::Singleton<Place>
{
	std::vector<std::vector<Sector>> m_sectors;

public:
	explicit Place();

public:
	void SetPosition(int x, int y);
	std::vector<Sector> GetInterestedSectors(int x, int y);
};
