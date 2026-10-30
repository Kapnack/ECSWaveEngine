#pragma once

#include <list>
#include <thread>
#include <vector>

using namespace std;

template<typename T>
concept VoidTask = invocable<T> && same_as<invoke_result_t<T>, void>;

static class Parallel
{

public:

	template<VoidTask... Methods>
	static void WaitTask(Methods... methods)
	{
		const int methodsSize = sizeof...(methods);

		thread** threads = new thread * [methodsSize];

		int i = 0;
		((threads[i++] = new thread(methods)), ...);

		for (int j = 0; j < methodsSize; ++j)
			threads[j]->join();

		for (int j = 0; j < methodsSize; ++j)
			delete threads[j];

		delete[] threads;
	}

	static thread ForTask(int startInclusive, int endExclusive, void(*action)(int))
	{
		return thread([startInclusive, endExclusive, action]() {For(startInclusive, endExclusive, action); });
	}

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
	static thread ForEachTask(T* array, int size, void(*action)(T*))
	{
		return thread([array, size, action]() {ForEach(array, size, action); });
	}

	template<typename T>
	static thread ForEachTask(vector<T>& vector, int size, void(*action)(T*))
	{
		return thread([array, size, action]() {ForEach(vector, size, action); });
	}

	template<typename T>
	static thread ForEachTask(list<T>& list, int size, void(*action)(T*))
	{
		return thread([array, size, action]() {ForEach(list, size, action); });
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

	template<typename T>
	static void ForEach(vector<T>& vector, void(*action)(T*))
	{
		thread** threads = new thread * [vector.size()];

		for (int i = 0; i < vector.size(); ++i)
		{
			T* element = vector[i];
			threads[i] = new thread([element, action]() {(*action)(element); });
		}

		for (int i = 0; i < size; ++i)
			threads[i]->join();

		for (int i = 0; i < size; ++i)
			delete threads[i];

		delete[] threads;
	}

	template<typename T>
	static void ForEach(list<T>& list, void(*action)(T*))
	{
		thread** threads = new thread * [list.size()];

		for (int i = 0; i < list.size(); ++i)
		{
			T* element = list[i];
			threads[i] = new thread([element, action]() {(*action)(element); });
		}

		for (int i = 0; i < size; ++i)
			threads[i]->join();

		for (int i = 0; i < size; ++i)
			delete threads[i];

		delete[] threads;
	}
};