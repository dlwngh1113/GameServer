#pragma once
#include "Place.h"

class MetaDatas
{
private:
	static MetaDatas s_instance;
	std::unordered_map<int, Place*> m_places;

private:
	MetaDatas() = default;

	void LoadMetaDatas();

	//
	// Place
	//

	void AddPlace(Place* place);

public:
	~MetaDatas();
	MetaDatas(const MetaDatas& other) = delete;
	MetaDatas& operator=(const MetaDatas& other) = delete;

	void Initialize();
	Place* GetPlace(int id);

public:

	static MetaDatas& GetInstance() 
	{
		return s_instance;
	}
};

