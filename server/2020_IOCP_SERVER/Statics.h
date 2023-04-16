#pragma once
#include "ObjectPool.h"
#include "ThreadPool.h"

class Statics
{
public:
	static ThreadPool s_threadPool;
	static ObjectPool<OVER_EX> s_overlappedPool;
};