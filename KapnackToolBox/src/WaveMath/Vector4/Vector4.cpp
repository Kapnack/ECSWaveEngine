#include "Vector4.h"

#include "WaveMath/Vector3/Vector3.h"
#include "WaveMath/WaveMath/WaveMath.h"

#include <cfloat>

Vector4::Vector4()
{
}

Vector4::Vector4(const Vector4& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;
}

Vector4::Vector4(Vector3 vector3)
{
	x = vector3.x;
	y = vector3.y;
	z = vector3.z;
	w = 1.0f;
}

Vector4::Vector4(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

float Vector4::Magnitude()
{
	return Magnitude(*this);
}

Vector4 Vector4::Normalized()
{
	return Normalized(*this);
}

void Vector4::Normalize()
{
	*this = Normalized();
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

Vector4 Vector4::operator/(float scalar) const
{
	return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
}

void Vector4::operator/=(float scalar)
{
	*this = *this / scalar;
}

Vector4 Vector4::Normalized(Vector4 vector4)
{
	float mag = vector4.Magnitude();

	if (mag < WaveMath::Epsilon())
		return Vector4::Zero();

	if (WaveMath::Abs(mag - 1.0f) < WaveMath::Epsilon())
		return vector4;

	return vector4 / mag;
}

float Vector4::Magnitude(Vector4 vector4)
{
	return WaveMath::SqrF(SqrMagnitude(vector4));
}

float Vector4::SqrMagnitude(Vector4 vector4)
{
	return Dot(vector4, vector4);
}

float Vector4::Dot(Vector4 vector4A, Vector4 vector4B)
{
	return vector4A.x * vector4B.x + vector4A.y * vector4B.y + vector4A.z * vector4B.z + vector4A.w * vector4B.w;
}
