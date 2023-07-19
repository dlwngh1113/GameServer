#pragma once
#include "ICreator.h"

template <typename TKey, typename TValue>
class IFactory
{
protected:
	std::unordered_map<TKey, std::unique_ptr<ICreator<TValue>>> m_creators;

public:
	virtual ~IFactory();
	virtual std::shared_ptr<TValue> Create(TKey key) = 0;
};

template<typename TKey, typename TValue>
inline IFactory<TKey, TValue>::~IFactory()
{
	m_creators.clear();
}