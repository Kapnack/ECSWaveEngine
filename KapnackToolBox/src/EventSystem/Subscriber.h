#pragma once

struct Subscriber
{
	void* instance = nullptr;
	void* method = nullptr;
	void (*invoke)(void*, void*, const void*);
};