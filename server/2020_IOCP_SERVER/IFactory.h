#pragma once

template <class TKey, class TValue>
class IFactory
{
protected:
public:
	virtual TValue* CreateInstance(TKey key) = 0;
};