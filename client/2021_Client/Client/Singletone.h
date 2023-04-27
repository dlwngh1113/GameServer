#pragma once

template<typename T>
class Singletone
{
	static T* s_instance;

public:
	Singletone();
	virtual ~Singletone();
	Singletone(const Singletone& other) = delete;
	Singletone(Singletone&& other) = delete;
	Singletone& operator=(const Singletone& other) = delete;
	Singletone& operator=(Singletone&& other) = delete;

	static T* GetInstance();
};