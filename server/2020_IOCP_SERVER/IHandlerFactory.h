#pragma once

template <class TKey, class TValue>
class IHandlerFactory
{
	std::unordered_map<Tkey, TValue> handlers;
protected:
	void AddHandler(TKey key);
public:

};