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

short WaveMath::Clamp(short value, short min, short max)
{
	return Min(Max(value, min), max);
}

int WaveMath::Clamp(int value, int min, int max)
{
	return Min(Max(value, min), max);
}

float WaveMath::Clamp01(float value)
{
	return Clamp(value, 0.0f, 1.0f);
}

float WaveMath::Clamp(float value, float min, float max)
{
	return Min(Max(value, min), max);
}

double WaveMath::Clamp01(double value)
{
	return Clamp(value, 0.0, 1.0);
}

double WaveMath::Clamp(double value, double min, double max)
{
	return Min(Max(value, min), max);
}

float WaveMath::Sqr(float number)
{
	if (number < 0 || number == 0)
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

double WaveMath::Sqr(double number)
{
	if (number < 0 || number == 0)
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

short WaveMath::Max(short a, short b)
{
	return a - ((a - b) & ((a - b) >> 15));
}

short WaveMath::Min(short a, short b)
{
	return b + ((a - b) & ((a - b) >> 15));
}

int WaveMath::Max(int a, int b)
{
	return a - ((a - b) & ((a - b) >> 31));
}

int WaveMath::Min(int a, int b)
{
	return b + ((a - b) & ((a - b) >> 31));
}

float WaveMath::Max(float a, float b)
{
	uint32_t bits = std::bit_cast<uint32_t>(a - b);

	uint32_t sign = bits & 0x7FFFFFFF;

	return a - (bits & (sign));
}

float WaveMath::Min(float a, float b)
{
	uint32_t bits = std::bit_cast<uint32_t>(a - b);

	uint32_t sign = bits & 0x7FFFFFFF;

	return b + (bits & (sign));
}

double WaveMath::Max(double a, double b)
{
	uint64_t bits = std::bit_cast<uint64_t>(a - b);

	uint64_t sign = bits & 0x7FFFFFFFFFFFFFFFULL;

	return a - (bits & (sign));
}

double WaveMath::Min(double a, double b)
{
	uint64_t bits = std::bit_cast<uint64_t>(a - b);

	uint64_t sign = bits & 0x7FFFFFFFFFFFFFFFULL;

	return b + (bits & (sign));
}

short WaveMath::Opposite(short number)
{
	const short mask = -1;
	return (number + mask) ^ mask;
}

int WaveMath::Opposite(int number)
{
	const int mask = -1;
	return (number + mask) ^ mask;
}

float WaveMath::Opposite(float number)
{
	uint32_t bits = std::bit_cast<uint32_t>(number);

	bits ^= 0x80000000;

	return std::bit_cast<float>(bits);
}

double WaveMath::Opposite(double number)
{
	uint64_t bits = std::bit_cast<uint64_t>(number);

	bits ^= 0x8000000000000000ULL;

	return std::bit_cast<double>(bits);
}