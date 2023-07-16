#pragma once

template <typename TKey, typename TValue>
class IFactory
{
protected:
	std::unordered_map<TKey, TValue> m_creators;
};