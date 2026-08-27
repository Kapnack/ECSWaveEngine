#include "WaveMath.h"
#include <bit>

float WaveMath::Epsilon()
{
	return 1e-05f;
}

bool WaveMath::Approximately(float a, float b)
{
	return Abs(b - a) < Epsilon();
}

float WaveMath::Abs(float number)
{
#ifdef _WIN32
	uint32_t bits = std::bit_cast<uint32_t>(number);
#elif _WIN64
	uint64_t bits = std::bit_cast<uint64_t>(number);
#endif

	bits &= 0x7FFFFFFF;

	return std::bit_cast<float>(bits);
}

int WaveMath::Abs(int number)
{
	int mask = number >> 31;

	return (number + mask) ^ mask;
}

float WaveMath::Opposite(float number)
{
#ifdef _WIN32
	uint32_t bits = std::bit_cast<uint32_t>(number);
#elif _WIN64
	uint64_t bits = std::bit_cast<uint64_t>(number);
#endif

	bits ^= 0x80000000;

	return std::bit_cast<float>(bits);
}

float WaveMath::Sqrt(float number)
{
	if (number < 0)
		return 0;

	if (number == 0)
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

int WaveMath::Opposite(int number)
{
	const int mask = -1;
	return (number + mask) ^ mask;
}
