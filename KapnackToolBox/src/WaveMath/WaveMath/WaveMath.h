#pragma once

#include "Export.h"
#include <type_traits>

template<typename T>
concept SignableObject = std::is_arithmetic_v<T>;

WAVEEXPORT class WaveMath
{
public:

	static const float epsilon;

	WAVEEXPORT static bool Approximately(float a, float b);

	WAVEEXPORT static float Abs(float number);
	WAVEEXPORT static int Abs(int number);

	template<SignableObject T>
	static int Sign(T number)
	{
		return static_cast<int>((number > 0) - (number < 0));
	}

	WAVEEXPORT static int Opposite(int number);
	WAVEEXPORT static float Opposite(float number);
};

