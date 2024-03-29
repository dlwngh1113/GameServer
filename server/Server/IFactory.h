#pragma once
#include "ICreator.h"

namespace Core
{
	template <typename TKey, typename TValue>
	class IFactory
	{
	protected:
		unordered_map<TKey, unique_ptr<ICreator<TValue>>> m_creators;

		ICreator<TValue>* GetCreator(TKey key)
		{
			auto it = m_creators.find(key);
			if (it != m_creators.end())
				return it->second.get();

			return nullptr;
		}

		void AddCreator(TKey key, unique_ptr<ICreator<TValue>>&& creator);

	public:
		virtual ~IFactory();
	};

	template<typename TKey, typename TValue>
	inline void IFactory<TKey, TValue>::AddCreator(TKey key, unique_ptr<ICreator<TValue>>&& creator)
	{
		m_creators.insert(make_pair(key, move(creator)));
	}

	template<typename TKey, typename TValue>
	inline IFactory<TKey, TValue>::~IFactory()
	{
		m_creators.clear();
	}
}