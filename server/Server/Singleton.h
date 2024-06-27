#pragma once

namespace Core
{
	template <typename T>
	class Singleton
	{
	protected:
		Singleton() {}
		virtual ~Singleton() {}

	public:
		static T& instance() { 
			static T s_instance;
			return s_instance; }

		Singleton operator=(const Singleton& other) = delete;
		Singleton(const Singleton& other) = delete;
	};
}