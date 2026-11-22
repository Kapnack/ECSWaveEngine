#pragma once

#include <list>
#include <thread>
#include <vector>
#include <concepts>
#include <type_traits>

#include "WaveMath/WaveMath/WaveMath.h"

using namespace std;

template<typename T>
concept VoidTask = invocable<T> && same_as<invoke_result_t<T>, void>;

template<typename T>
concept IntAction = invocable<T, int>&& same_as<invoke_result_t<T, int>, void>;

static class Parallel
{
private:

public:

	template<VoidTask... Methods>
	static void WaitTask(Methods... methods)
	{
		const int methodsSize = sizeof...(methods);

		void(**meths)(void) = static_cast<void(**)(void)>(malloc(sizeof(void(*)(void)) * methodsSize));

		int i = 0;
		((meths[i++] = static_cast<void(*)(void)>(methods)), ...);

		const int hw = static_cast<int>(thread::hardware_concurrency());
		const int workerCount = WaveMath::MinI(methodsSize, hw > 0 ? hw : 4);

		const int baseCount = methodsSize / workerCount;
		const int remainder = methodsSize % workerCount;

		thread** threads = new thread * [workerCount];

		int begin = 0;
		for (int j = 0; j < workerCount; ++j)
		{
			const int end = begin + baseCount + (j < remainder ? 1 : 0);

			threads[j] = new thread([begin, end, &meths]()
				{
					for (int j = begin; j < end; ++j)
						meths[j]();
				});

			begin = end;
		}

		for (int j = 0; j < methodsSize; ++j)
			threads[j]->join();

		for (int j = 0; j < methodsSize; ++j)
			meths[j] = nullptr;

		free(meths);

		for (int h = 0; h < methodsSize; ++h)
			delete threads[h];

		delete[] threads;
	}

	template<IntAction Method>
	static thread ForTask(int startInclusive, int endExclusive, Method action)
	{
		return thread([startInclusive, endExclusive, action]() {For(startInclusive, endExclusive, action); });
	}

	template<IntAction Method>
	static void For(int startInclusive, int endExclusive, Method action)
	{
		const int totalElements = endExclusive - startInclusive;

		const int hw = static_cast<int>(thread::hardware_concurrency());
		const int workerCount = WaveMath::MinI(totalElements, hw > 0 ? hw : 4);

		const int baseCount = totalElements / workerCount;
		const int remainder = totalElements % workerCount;

		thread** threads = new thread * [workerCount];

		int begin = startInclusive;
		for (int i = 0; i < workerCount; ++i)
		{
			const int end = begin + baseCount + (i < remainder ? 1 : 0);

			threads[i] = new thread([begin, end, action]()
				{
					for (int j = begin; j < end; ++j)
						action(j);
				});

			begin = end;
		}

		for (int i = 0; i < workerCount; ++i)
			threads[i]->join();

		for (int i = 0; i < workerCount; ++i)
			delete threads[i];

		delete[] threads;
	}

	template<typename T>
	static thread ForEachTask(T* array, int size, void(*action)(T))
	{
		return thread([array, size, action]() {ForEach(array, size, action); });
	}

	template<typename T>
	static thread ForEachTask(vector<T>& vector, int size, void(*action)(T))
	{
		return thread([vector, size, action]() {ForEach(vector, size, action); });
	}

	template<typename T>
	static thread ForEachTask(list<T>& list, int size, void(*action)(T))
	{
		return thread([list, size, action]() {ForEach(list, size, action); });
	}

	template<typename T>
	static void ForEach(T* array, int size, void(*action)(T))
	{
		const int hw = static_cast<int>(thread::hardware_concurrency());
		const int workerCount = WaveMath::MinI(size, hw > 0 ? hw : 4);

		const int baseCount = size / workerCount;
		const int remainder = size % workerCount;

		thread** threads = new thread * [workerCount];

		int begin = 0;
		for (int i = 0; i < workerCount; ++i)
		{
			const int end = begin + baseCount + (i < remainder ? 1 : 0);

			threads[i] = new thread([begin, end, &array, action]()
				{
					for (int j = begin; j < end; ++j)
						(*action)((array + j));
				});

			begin = end;
		}

		for (int i = 0; i < workerCount; ++i)
			threads[i]->join();

		for (int i = 0; i < workerCount; ++i)
			delete threads[i];

		delete[] threads;
	}

	template<typename T>
	static void ForEach(vector<T>& vector, void(*action)(T))
	{
		const int vectorSize = vector.size();

		const int hw = static_cast<int>(thread::hardware_concurrency());
		const int workerCount = WaveMath::MinI(vectorSize, hw > 0 ? hw : 4);

		const int baseCount = vectorSize / workerCount;
		const int remainder = vectorSize % workerCount;

		thread** threads = new thread * [workerCount];

		int begin = 0;
		for (int i = 0; i < workerCount; ++i)
		{
			const int end = begin + baseCount + (i < remainder ? 1 : 0);

			threads[i] = new thread([begin, end, &vector, action]()
				{
					for (int j = begin; j < end; ++j)
						(*action)((vector[j]));
				});

			begin = end;
		}

		for (int i = 0; i < workerCount; ++i)
			threads[i]->join();

		for (int i = 0; i < workerCount; ++i)
			delete threads[i];

		delete[] threads;
	}

	template<typename T>
	static void ForEach(list<T>& list, void(*action)(T))
	{
		const int listSize = list.size();

		const int hw = static_cast<int>(thread::hardware_concurrency());
		const int workerCount = WaveMath::MinI(listSize, hw > 0 ? hw : 4);

		const int baseCount = listSize / workerCount;
		const int remainder = listSize % workerCount;

		thread** threads = new thread * [workerCount];

		int begin = 0;
		for (int i = 0; i < workerCount; ++i)
		{
			const int end = begin + baseCount + (i < remainder ? 1 : 0);

			threads[i] = new thread([begin, end, &list, action]()
				{
					for (int j = begin; j < end; ++j)
						(*action)((list[j]));
				});

			begin = end;
		}

		for (int i = 0; i < workerCount; ++i)
			threads[i]->join();

		for (int i = 0; i < workerCount; ++i)
			delete threads[i];

		delete[] threads;
	}
};