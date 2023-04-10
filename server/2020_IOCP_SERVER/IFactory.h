#pragma once

template <typename TKey, typename TValue>
class IFactory
{
public:
	virtual TValue* CreateInstance(TKey key) = 0;
};