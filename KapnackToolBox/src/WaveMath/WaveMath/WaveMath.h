#pragma once

#include "Export.h"
#include <type_traits>

template<typename T>
concept SignableObject = std::is_arithmetic_v<T>;

class WAVEEXPORT WaveMath
{
public:

	static float Epsilon();

	static float PI();

	static bool Approximately(float a, float b);

	static float Abs(float number);
	static int Abs(int number);

	template<SignableObject T>
	static T Clamp(T value, T min, T max)
	{
		return value < min ? min : value > max ? max : value;
	}

	template<SignableObject T>
	static T Clamp01(T value)
	{
		return Clamp(value, 0.0f, 1.0f);
	}

	template<SignableObject T>
	static int Sign(T number)
	{
		return static_cast<int>((number > 0) - (number < 0));
	}

	static int Min(int a, int b);

	static int Opposite(int number);
	static float Opposite(float number);

	static float Sqr(float number);

	static float Deg2Rad(float number);
	static float Rad2Deg(float number);
};

