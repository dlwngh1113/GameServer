#include "stdafx.h"
#include "ThreadPool.h"

void ThreadPool::Work()
{
	while (true)
	{

	}
}

ThreadPool::ThreadPool(size_t size)
{
}

ThreadPool::~ThreadPool()
{
}

void ThreadPool::EnqueWork(std::function<void()> work)
{
}
