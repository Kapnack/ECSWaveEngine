#pragma once

#include <thread>

using namespace std;

static class Parallel
{

public:

	static void For(int startInclusive, int endExclusive, void(*action)(int))
	{
		int threadsSize = endExclusive - startInclusive;
		thread** threads = new thread * [threadsSize];

		for (int i = startInclusive; i < endExclusive; ++i)
			threads[i - startInclusive] = new thread([i, action]() {(*action)(i); });

		for (int i = 0; i < threadsSize; ++i)
			threads[i]->join();

		for (int i = 0; i < threadsSize; ++i)
			delete threads[i];

		delete[] threads;
	}

	template<typename T>
	static void ForEach(T* array, int size, void(*action)(T*))
	{
		thread** threads = new thread * [size];

		for (int i = 0; i < size; ++i)
		{
			T* element = (array + i);
			threads[i] = new thread([element, action]() {(*action)(element); });
		}

		for (int i = 0; i < size; ++i)
			threads[i]->join();

		for (int i = 0; i < size; ++i)
			delete threads[i];

		delete[] threads;
	}
};