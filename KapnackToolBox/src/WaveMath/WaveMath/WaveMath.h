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

	static short Abs(short number);
	static int Abs(int number);
	static float Abs(float number);
	static double Abs(double number);

	static short Clamp(short value, short min, short max);
	static int Clamp(int value, int min, int max);
	static float Clamp01(float value);
	static float Clamp(float value, float min, float max);
	static double Clamp01(double value);
	static double Clamp(double value, double min, double max);

	template<SignableObject T>
	static int Sign(T number)
	{
		return static_cast<int>((number > 0) - (number < 0));
	}

	static short Max(short a, short b);
	static short Min(short a, short b);
	static int Max(int a, int b);
	static int Min(int a, int b);
	static float Max(float a, float b);
	static float Min(float a, float b);
	static double Max(double a, double b);
	static double Min(double a, double b);

	static short Opposite(short number);
	static int Opposite(int number);
	static float Opposite(float number);
	static double Opposite(double number);

	static float Sqr(float number);
	static double Sqr(double number);

	static float Deg2Rad(float number);
	static float Rad2Deg(float number);
};

