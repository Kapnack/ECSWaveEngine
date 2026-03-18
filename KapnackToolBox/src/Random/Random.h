#pragma once

#include <random>

using namespace std;

namespace WaveEngine
{
	class Random
	{
	private:

		static mt19937 randomEngine;
		static uniform_int_distribution<mt19937::result_type> distribution;

	public:

		static void Init()
		{
			randomEngine.seed(random_device()());
		}

		static float Float()
		{
			return static_cast<float>(distribution(randomEngine)) / static_cast<float>(numeric_limits<uint32_t>::max());
		}
	};
}