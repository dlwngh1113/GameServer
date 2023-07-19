#pragma once
#include "ICreator.h"

template<typename THandlerType>
class HandlerCreator : public ICreator<THandlerType>
{
public:
	virtual std::shared_ptr<THandlerType> Create() override;
};

template<typename THandlerType>
inline std::shared_ptr<THandlerType> HandlerCreator<THandlerType>::Create()
{
	return std::shared_ptr<THandlerType>();
}
