#pragma once

template<typename TBase>
class ICreator
{
public:
	virtual ~ICreator() {}
	virtual std::shared_ptr<TBase> Create() = 0;
};

template<typename TBase, typename TProduct>
class ProductCreator : public ICreator<TBase>
{
public:
	virtual std::shared_ptr<TBase> Create() { return std::make_shared<TProduct>(); }
};
