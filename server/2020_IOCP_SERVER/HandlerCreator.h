#pragma once
#include "IRequestHandler.h"

class IHandlerCreator
{
public:
	virtual std::shared_ptr<IRequestHandler> CreateHandler() = 0;
};

template<typename T>
class HandlerCreator : public IHandlerCreator
{
public:
	virtual std::shared_ptr<IRequestHandler> CreateHandler() override;
};

template<typename T>
inline std::shared_ptr<IRequestHandler> HandlerCreator<T>::CreateHandler()
{
	return std::shared_ptr<IRequestHandler>();
}
