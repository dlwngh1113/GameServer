#include "stdafx.h"
#include "ThreadPool.h"
#include "Logger.h"

void ThreadPool::Work()
{
	while (true)
	{
		std::unique_lock<std::mutex> lock{ m_lock };
		
		// work가 생길 때까지 대기
		m_conditionVariable.wait(lock, [&]() { return !m_works.empty(); });

		std::function<void()> work = m_works.front();
		m_works.pop();
		lock.unlock();

		try
		{
			work();
		}
		catch (std::exception& ex)
		{
			Log(ex.what());
		}
	}
}

ThreadPool::ThreadPool(size_t size)
{
	for (int i=0; i<size;++i)
		m_workers.emplace_back(std::thread{ [this]() { Work(); } });
}

ThreadPool::~ThreadPool()
{
	while (!m_works.empty())
		m_works.pop();

	m_conditionVariable.notify_all();

	for (auto& worker : m_workers)
		worker.join();
}

void ThreadPool::EnqueWork(std::function<void()>&& work)
{
	{
		std::lock_guard lock{ m_lock };
		m_works.emplace(work);
	}

	m_conditionVariable.notify_one();
}
