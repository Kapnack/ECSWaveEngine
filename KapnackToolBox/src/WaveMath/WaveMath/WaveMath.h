#pragma once

#include "Export.h"
#include <type_traits>

template<typename T>
concept SignableObject = std::is_arithmetic_v<T>;

class WAVEEXPORT WaveMath
{
public:

	static float Epsilon();

	static bool Approximately(float a, float b);

	static float Abs(float number);
	static int Abs(int number);

	template<SignableObject T>
	static int Sign(T number)
	{
		return number >= 0 ? 1 : -1;//static_cast<int>((number > 0) - (number < 0));
	}

	static int Opposite(int number);
	static float Opposite(float number);

	static float Sqrt(float number);
};

