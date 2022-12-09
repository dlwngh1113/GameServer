#pragma once

template<class T>
class Singletone
{
	static T* s_instance;

public:
	static T* GetInstance()
	{
		if (s_instance == nullptr)
		{
			s_instance = new T();
		}

		return s_instance;
	}
};

template<class T>
T* Singletone<T>::s_instance = nullptr;
