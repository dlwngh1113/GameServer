#pragma once

namespace ClientFramework
{
	template <typename T>
	class Singleton
	{
	protected:
		static T s_instance;

	public:
		static T& instance() { return s_instance; }

		Singleton operator=(const Singleton& other) = delete;
		Singleton(const Singleton& other) = delete;
	};
}