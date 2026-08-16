#include "WaveMath.h"
#include <bit>

const float WaveMath::epsilon = 1e-05f;

bool WaveMath::Approximately(float a, float b)
{
	return Abs(b - a) < epsilon;
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

int WaveMath::Sign(int number)
{
	return (number > 0) - (number < 0);
}

int WaveMath::Sign(float number)
{

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

int WaveMath::Opposite(int number)
{
	const int mask = -1;
	return (number + mask) ^ mask;
}
