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

	static short ClampS(short value, short min, short max);
	static int ClampI(int value, int min, int max);
	static float ClampF01(float value);
	static float ClampF(float value, float min, float max);
	static double ClampD01(double value);
	static double ClampD(double value, double min, double max);

	template<SignableObject T>
	static int Sign(T number)
	{
		return static_cast<int>((number > 0) - (number < 0));
	}

	static short MaxS(short a, short b);
	static short MinS(short a, short b);
	static int MaxI(int a, int b);
	static int MinI(int a, int b);
	static float MaxF(float a, float b);
	static float MinF(float a, float b);
	static double MaxD(double a, double b);
	static double MinD(double a, double b);

	static short OppositeS(short number);
	static int OppositeI(int number);
	static float OppositeF(float number);
	static double OppositeD(double number);

	static float SqrF(float number);
	static double SqrT(double number);

	static float Deg2Rad(float number);
	static float Rad2Deg(float number);
};

