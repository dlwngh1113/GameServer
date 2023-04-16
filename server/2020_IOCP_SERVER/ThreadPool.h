#pragma once

class ThreadPool
{
private:
	std::vector<std::thread> m_workers;
	std::queue<std::function<void()>> m_works;
	std::mutex m_lock;
	std::condition_variable m_conditionVariable;

private:
	void Work();

public:
	explicit ThreadPool(size_t size);
	virtual ~ThreadPool();

	void EnqueWork(std::function<void()> work);
};

