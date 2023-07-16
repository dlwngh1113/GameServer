#pragma once

template<typename T>
class HandlerCreator
{
public:
	std::shared_ptr<T> Create();
};

template<typename T>
inline std::shared_ptr<T> HandlerCreator<T>::Create()
{
	return std::shared_ptr<T>();
}
