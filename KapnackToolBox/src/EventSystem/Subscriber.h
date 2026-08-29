#pragma once

template<typename TReturnType>
struct Subscriber
{
	void* instance = nullptr;
	void* method = nullptr;
	TReturnType(*invoke)(void*, void*, const void*);
};