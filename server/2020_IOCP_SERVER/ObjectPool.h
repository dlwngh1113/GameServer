#pragma once
#include"Logger.h"

template <typename T>
class ObjectPool
{
	std::mutex m_lock;
	Concurrency::concurrent_queue<T*> m_pool;
public:
	explicit ObjectPool(int size);
	virtual ~ObjectPool();

	void PushObject(T* obj);
	T* PopObject();
};

template<typename T>
inline ObjectPool<T>::ObjectPool(int size)
{
	for (int i = 0; i < size; ++i)
	{
		T* data = new T;
		m_pool.push(data);
	}
}

template<typename T>
inline ObjectPool<T>::~ObjectPool()
{
	T* data = nullptr;

	while (m_pool.try_pop(data))
		delete data;
}

template<typename T>
inline void ObjectPool<T>::PushObject(T* obj)
{
	m_pool.push(obj);
}

template<typename T>
inline T* ObjectPool<T>::PopObject()
{
	T* data = nullptr;

	m_pool.try_pop(data);

	if (data == nullptr)
		data = new T;
	ZeroMemory(data, sizeof(T));
	
	return data;
}
