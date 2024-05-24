#pragma once

namespace ClientFramework
{
	template <typename T>
	class Singleton
	{
	protected:
		static T s_instance;
		Singleton() {}

	public:
		static T& instance() { return s_instance; }
		virtual ~Singleton() {}

		Singleton operator=(const Singleton& other) = delete;
		Singleton(const Singleton& other) = delete;
	};
}