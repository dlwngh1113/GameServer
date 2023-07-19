#pragma once

template<typename TBaseType>
class ICreator
{
public:
	virtual ~ICreator() {}
	virtual std::shared_ptr<TBaseType> Create() = 0;
};