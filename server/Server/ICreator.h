#pragma once

namespace Core
{
	template<typename TBase>
	class ICreator
	{
	public:
		virtual ~ICreator() {}
		virtual shared_ptr<TBase> Create() = 0;
	};

	template<typename TBase, typename TProduct>
	class ProductCreator : public ICreator<TBase>
	{
	public:
		virtual shared_ptr<TBase> Create() { return make_shared<TProduct>(); }
	};
}