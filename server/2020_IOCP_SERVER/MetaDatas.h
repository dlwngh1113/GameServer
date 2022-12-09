#pragma once
#include"Singletone.h"
#include"Place.h"

class MetaDatas : Singletone<MetaDatas>
{
private:
	std::unordered_map<int, Place*> m_places;

public:
	void Init();
	Place* GetPlace(int id);
};

