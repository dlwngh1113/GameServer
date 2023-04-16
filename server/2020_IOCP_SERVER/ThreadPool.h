#pragma once

class ThreadPool
{
private:
	std::vector<std::thread> m_workers;
	std::mutex m_lock;
	std::condition_variable m_conditionVariable;

	void Work();
public:
	explicit ThreadPool(size_t size);
	virtual ~ThreadPool();

	void EnqueWork(std::function<void()> work);
};

