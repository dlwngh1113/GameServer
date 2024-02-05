#pragma once

class MetaDatas
{
private:
	static MetaDatas s_instance;

private:
	MetaDatas() = default;

	void LoadMetaDatas();

public:
	~MetaDatas();
	MetaDatas(const MetaDatas& other) = delete;
	MetaDatas& operator=(const MetaDatas& other) = delete;

	void Initialize();

public:

	static MetaDatas& GetInstance() 
	{
		return s_instance;
	}
};

