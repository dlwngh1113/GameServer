#pragma once

template<typename TProduct>
class ICreator
{
public:
	virtual ~ICreator() {}
	virtual std::shared_ptr<TProduct> Create() = 0;
};

template<typename TBase, typename TProduct>
class ProductCreator : public ICreator<TBase>
{
public:
	virtual std::shared_ptr<TBase> Create() { return std::make_shared<TProduct>(); }
};