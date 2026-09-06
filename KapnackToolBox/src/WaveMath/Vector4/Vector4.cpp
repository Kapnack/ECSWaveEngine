#include "Vector4.h"
#include "Vector4.h"

#include <cfloat>

Vector4::Vector4()
{
}

Vector4::Vector4(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vector4 Vector4::Zero()
{
	return Vector4(0.0f, 0.0f, 0.0f, 0.0f);
}

Vector4 Vector4::One()
{
	return Vector4(1.0f, 1.0f, 1.0f, 1.0f);
}

Vector4 Vector4::Min()
{
	return Vector4(FLT_MIN, FLT_MIN, FLT_MIN, FLT_MIN);
}

Vector4 Vector4::NMin()
{
	return -Min();
}

Vector4 Vector4::Max()
{
	return Vector4(FLT_MAX, FLT_MAX, FLT_MAX, FLT_MAX);
}

Vector4 Vector4::NMax()
{
	return -Max();
}

Vector4 Vector4::operator-() const
{
	return Vector4(-x, -y, -z, -w);
}
