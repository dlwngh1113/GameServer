#pragma once

template <typename TKey, typename TValue>
class IFactory
{
public:
	virtual std::shared_ptr<TValue> CreateInstance(TKey key) = 0;
};