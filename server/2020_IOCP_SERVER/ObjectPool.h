#pragma once
#include"Logger.h"

template <class T>
class ObjectPool
{
	std::mutex m_lock;
	std::queue<T*> m_pool;
public:
	ObjectPool(int size);
	virtual ~ObjectPool();

	void PushObject(T* obj);
	T* PopObject();
};

template<class T>
inline ObjectPool<T>::ObjectPool(int size)
{
	for (int i = 0; i < size; ++i)
	{
		T* data = new T;
		m_pool.push(data);
	}
}

template<class T>
inline ObjectPool<T>::~ObjectPool()
{
	while (!m_pool.empty())
	{
		T* data = m_pool.front();
			delete data;

		m_pool.pop();
	}
}

template<class T>
inline void ObjectPool<T>::PushObject(T* obj)
{
	m_lock.lock();
	m_pool.push(obj);
	m_lock.unlock();
}

template<class T>
inline T* ObjectPool<T>::PopObject()
{
	T* data = nullptr;

	if (m_pool.empty())
		throw std::exception{ "오브젝트 풀이 비어있습니다." };

	data = m_pool.front();
	m_pool.pop();
	ZeroMemory(data, sizeof(T));

	return data;
}
