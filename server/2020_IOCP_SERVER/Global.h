#pragma once
#include "ObjectPool.h"
#include "ThreadPool.h"

class Global
{
	static Global s_instance;
	
public:
	Global();
	virtual ~Global();

	ThreadPool threadPool{ MAX_THREAD_COUNT };
	ObjectPool<OVER_EX> overlappedPool{ MAX_USER };

	static Global& GetInstance() { return s_instance; }
};