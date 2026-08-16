#pragma once

#include "Export.h"

template<typename T>
concept SignableObject = std::is_arithmetic_v<T> || 
	requires(T a, T b) 
{
		{ a < b } -> std::convertible_to<bool>;
		{ a > b } -> std::convertible_to<bool>;
};;

WAVEEXPORT class WaveMath
{
public:

	static const float epsilon;

	WAVEEXPORT static bool Approximately(float a, float b);

	WAVEEXPORT static float Abs(float number);
	WAVEEXPORT static int Abs(int number);

	template<SignableObject T>
	WAVEEXPORT static int Sign(T number)
	{
		return static_cast<int>((number > 0) - (number < 0));
	}

	WAVEEXPORT static int Opposite(int number);
	WAVEEXPORT static float Opposite(float number);
};

