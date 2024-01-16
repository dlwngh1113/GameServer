#pragma once
#include "ICreator.h"

class BaseRequestHandler;

template <typename THandlerType>
class IHandlerCreator : public ICreator<THandlerType>
{
public:
	virtual ~IHandlerCreator() {}
	virtual std::shared_ptr<THandlerType> Create() = 0;
};
