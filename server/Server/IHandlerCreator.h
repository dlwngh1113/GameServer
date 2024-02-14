#pragma once
#include "ICreator.h"

namespace Core
{
	template <typename THandlerType>
	class IHandlerCreator : public ICreator<THandlerType>
	{
	public:
		virtual ~IHandlerCreator() {}
		virtual shared_ptr<THandlerType> Create() = 0;
	};
}