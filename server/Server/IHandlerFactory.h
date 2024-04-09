#pragma once
#include "IFactory.h"

namespace Core
{
	class BaseCommandHandler; 
	
	class IHandlerFactory : public IFactory<short, BaseCommandHandler>
	{
	public:
		IHandlerFactory();
		virtual ~IHandlerFactory();

		virtual std::shared_ptr<BaseCommandHandler> Create(short type) = 0;

		template<typename T>
		void AddHandlerCreator(short key);
	};

	template<typename T>
	inline void IHandlerFactory::AddHandlerCreator(short key)
	{
		AddCreator(key, std::make_unique<ProductCreator<BaseCommandHandler, T>>());
	}
}