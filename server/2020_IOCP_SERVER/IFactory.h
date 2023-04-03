#pragma once

template <typename TKey, typename TValue>
class IFactory
{
protected:
public:
	virtual TValue* CreateInstance(TKey key) = 0;
};