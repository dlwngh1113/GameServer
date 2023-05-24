#pragma once

template<typename T>
class Singleton
{
private:
	static T* s_instance;

protected:
	Singleton()
	{
	}
	virtual ~Singleton()
	{
		if (s_instance)
			delete s_instance;
	}

public:
	Singleton(const Singleton& other) = delete;
	Singleton(Singleton&& other) = delete;
	Singleton& operator=(const Singleton& other) = delete;
	Singleton& operator=(Singleton&& other) = delete;

	static T* GetInstance()
	{
		if (s_instance == nullptr)
			s_instance = new T;

		return s_instance;
	}
};

template<typename T>
T* Singleton<T>::s_instance = nullptr;