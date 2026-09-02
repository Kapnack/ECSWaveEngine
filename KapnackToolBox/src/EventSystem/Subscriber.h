#pragma once

template<typename TReturn, typename... TParams>
struct Subscriber
{
	void* instance = nullptr;
	void* method = nullptr;
	TReturn(*invoke)(void*, void*, TParams...);
};