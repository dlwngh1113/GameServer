#pragma once
#include "ICreator.h"

template <typename TKey, typename TValue>
class IFactory
{
protected:
	std::unordered_map<TKey, std::unique_ptr<ICreator<TValue>>> m_creators;

protected:
	void AddCreator(TKey key, std::unique_ptr<ICreator<TValue>> creator);

public:
	virtual ~IFactory();
	virtual std::shared_ptr<TValue> Create(TKey key);
};

template<typename TKey, typename TValue>
inline void IFactory<TKey, TValue>::AddCreator(TKey key, std::unique_ptr<ICreator<TValue>> creator)
{
	m_creators.insert(key, creator);
}

template<typename TKey, typename TValue>
inline IFactory<TKey, TValue>::~IFactory()
{
	m_creators.clear();
}

template<typename TKey, typename TValue>
inline std::shared_ptr<TValue> IFactory<TKey, TValue>::Create(TKey key)
{
	return m_creators[key]->Create();
}
