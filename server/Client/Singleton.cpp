#include "pch.h"
#include "Singleton.h"

namespace ClientFramework
{
	template <typename T>
	T Singleton<T>::s_instance;
}