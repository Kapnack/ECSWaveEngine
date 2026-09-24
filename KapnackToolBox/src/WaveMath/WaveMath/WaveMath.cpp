#include "WaveMath.h"

#include <bit>
#include <cstdint>

float WaveMath::Epsilon()
{
	return 1e-05f;
}

float WaveMath::PI()
{
	return 3.14159274f;
}

bool WaveMath::Approximately(float a, float b)
{
	return Abs(b - a) < Epsilon();
}

short WaveMath::Abs(short number)
{
	short mask = number >> 15;

	return (number + mask) ^ mask;
}

int WaveMath::Abs(int number)
{
	int mask = number >> 31;

	return (number + mask) ^ mask;
}

float WaveMath::Abs(float number)
{
	uint32_t bits = std::bit_cast<uint32_t>(number);

	bits &= 0x7FFFFFFF;

	return std::bit_cast<float>(bits);
}

double WaveMath::Abs(double number)
{
	uint64_t bits = std::bit_cast<uint64_t>(number);

	bits &= 0x7FFFFFFFFFFFFFFFULL;

	return std::bit_cast<double>(bits);
}

short WaveMath::ClampS(short value, short min, short max)
{
	return MinS(MaxS(value, min), max);
}

int WaveMath::ClampI(int value, int min, int max)
{
	return MinI(MaxI(value, min), max);
}

float WaveMath::ClampF01(float value)
{
	return ClampF(value, 0.0f, 1.0f);
}

float WaveMath::ClampF(float value, float min, float max)
{
	return MinF(MaxF(value, min), max);
}

double WaveMath::ClampD01(double value)
{
	return ClampD(value, 0.0, 1.0);
}

double WaveMath::ClampD(double value, double min, double max)
{
	return MinD(MaxD(value, min), max);
}

float WaveMath::SqrF(float number)
{
	if (number <= 0)
		return 0;

	float guess = number * 0.5f;
	float betterGuess = 0;

	while (WaveMath::Abs(guess - betterGuess) > WaveMath::Epsilon())
	{
		betterGuess = guess;

		guess = WaveMath::Abs(guess + number / guess) * 0.5f;
	}

	return betterGuess;
}

double WaveMath::SqrT(double number)
{
	if (number <= 0)
		return 0;

	double guess = number * 0.5f;
	double betterGuess = 0;

	while (WaveMath::Abs(guess - betterGuess) > WaveMath::Epsilon())
	{
		betterGuess = guess;

		guess = WaveMath::Abs(guess + number / guess) * 0.5f;
	}

	return betterGuess;
}

float WaveMath::Deg2Rad(float number)
{
	return number * (PI() / 180.0f);
}

float WaveMath::Rad2Deg(float number)
{
	return number * (180.0f / PI());
}

short WaveMath::MaxS(short a, short b)
{
	return a - ((a - b) & ((a - b) >> 15));
}

short WaveMath::MinS(short a, short b)
{
	return b + ((a - b) & ((a - b) >> 15));
}

int WaveMath::MaxI(int a, int b)
{
	return a - ((a - b) & ((a - b) >> 31));
}

int WaveMath::MinI(int a, int b)
{
	return b + ((a - b) & ((a - b) >> 31));
}

float WaveMath::MaxF(float a, float b)
{
	uint32_t bits = std::bit_cast<uint32_t>(a - b);

	uint32_t sign = bits & 0x7FFFFFFF;

	return a - (bits & (sign));
}

float WaveMath::MinF(float a, float b)
{
	uint32_t bits = std::bit_cast<uint32_t>(a - b);

	uint32_t sign = bits & 0x7FFFFFFF;

	return b + (bits & (sign));
}

double WaveMath::MaxD(double a, double b)
{
	uint64_t bits = std::bit_cast<uint64_t>(a - b);

	uint64_t sign = bits & 0x7FFFFFFFFFFFFFFFULL;

	return a - (bits & (sign));
}

double WaveMath::MinD(double a, double b)
{
	uint64_t bits = std::bit_cast<uint64_t>(a - b);

	uint64_t sign = bits & 0x7FFFFFFFFFFFFFFFULL;

	return b + (bits & (sign));
}

short WaveMath::OppositeS(short number)
{
	const short mask = -1;
	return (number + mask) ^ mask;
}

int WaveMath::OppositeI(int number)
{
	const int mask = -1;
	return (number + mask) ^ mask;
}

float WaveMath::OppositeF(float number)
{
	uint32_t bits = std::bit_cast<uint32_t>(number);

	bits ^= 0x80000000;

	return std::bit_cast<float>(bits);
}

double WaveMath::OppositeD(double number)
{
	uint64_t bits = std::bit_cast<uint64_t>(number);

	bits ^= 0x8000000000000000ULL;

	return std::bit_cast<double>(bits);
}