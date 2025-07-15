#pragma once
#include "IFactory.h"

namespace Core
{
	class BaseCommandHandler; 
	
	class IHandlerFactory : public IFactory<int16_t, BaseCommandHandler>
	{
	public:
		IHandlerFactory();
		virtual ~IHandlerFactory();

		virtual std::shared_ptr<BaseCommandHandler> Create(int16_t type) = 0;

		template<typename T>
		void AddHandlerCreator(int16_t key);
	};

	template<typename T>
	inline void IHandlerFactory::AddHandlerCreator(int16_t key)
	{
		AddCreator(key, std::make_unique<ProductCreator<BaseCommandHandler, T>>());
	}
}