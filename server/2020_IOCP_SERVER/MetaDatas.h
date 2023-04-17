#pragma once
#include "Place.h"

class MetaDatas
{
private:
	static MetaDatas* s_instance;
	std::unordered_map<int, Place*> m_places;

public:
	~MetaDatas();

	void Initialize();
	Place* GetPlace(int id);

private:
	MetaDatas() = default;

	void LoadMetaDatas();

	//
	// Place
	//

	void AddPlace(Place* place);

public:

	static MetaDatas* GetInstance() 
	{
		if (s_instance == nullptr)
		{
			s_instance = new MetaDatas();
		}

		return s_instance;
	}
};

