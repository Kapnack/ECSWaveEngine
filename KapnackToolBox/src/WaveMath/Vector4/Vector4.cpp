#include "Vector4.h"

#include "WaveMath/Vector3/Vector3.h"
#include "WaveMath/WaveMath/WaveMath.h"

#include <cfloat>

Vector4::Vector4()
{
}

Vector4::Vector4(const Vector4& vector)
{
	x = vector.x;
	y = vector.y;
	z = vector.z;
	w = vector.w;
}

Vector4::Vector4(Vector3 vector)
{
	x = vector.x;
	y = vector.y;
	z = vector.z;
	w = 1.0f;
}

Vector4::Vector4(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

float Vector4::Magnitude() const
{
	return Magnitude(*this);
}

Vector4 Vector4::Normalized() const
{
	return Normalized(*this);
}

void Vector4::Normalize()
{
	*this = Normalized();
}

float Vector4::Dot(Vector4 other) const
{
	return Dot(*this, other);
}

bool Vector4::Approximately(Vector4 other) const
{
	return Approximately(*this, other);
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

Vector4 Vector4::operator+(Vector4 other) const
{
	return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
}

void Vector4::operator+=(Vector4 other)
{
	*this = *this + other;
}

Vector4 Vector4::operator-() const
{
	return Vector4(-x, -y, -z, -w);
}

Vector4 Vector4::operator-(Vector4 other) const
{
	return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
}

void Vector4::operator-=(Vector4 other)
{
	*this = *this - other;
}

Vector4 Vector4::operator*(Vector4 other) const
{
	return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
}

Vector4 Vector4::operator*(float scalar) const
{
	return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
}

void Vector4::operator*=(Vector4 other)
{
	*this = *this * other;
}

void Vector4::operator*=(float scalar)
{
	*this = *this * scalar;
}

Vector4 Vector4::operator/(float scalar) const
{
	return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
}

void Vector4::operator/=(float scalar)
{
	*this = *this / scalar;
}

bool Vector4::operator>(Vector4 other) const
{
	return x > other.x && y > other.y && z > other.z && w > other.w;
}

bool Vector4::operator<(Vector4 other) const
{
	return other > *this;
}

bool Vector4::operator==(Vector4 other) const
{
	return x == other.x && y == other.y && z == other.z && w == other.w;
}

bool Vector4::operator!=(Vector4 other) const
{
	return !(*this == other);
}

bool Vector4::operator>=(Vector4 other) const
{
	return *this > other || *this == other;
}

bool Vector4::operator<=(Vector4 other) const
{
	return *this < other || *this == other;
}

Vector4 Vector4::Normalized(Vector4 vector)
{
	float mag = vector.Magnitude();

	if (mag < WaveMath::Epsilon())
		return Vector4::Zero();

	if (WaveMath::Abs(mag - 1.0f) < WaveMath::Epsilon())
		return vector;

	return vector / mag;
}

float Vector4::Distance(Vector4 a, Vector4 b)
{
	return Magnitude(a - b);
}

float Vector4::Magnitude(Vector4 vector)
{
	return WaveMath::SqrF(SqrMagnitude(vector));
}

float Vector4::SqrMagnitude(Vector4 vector)
{
	return Dot(vector, vector);
}

float Vector4::Dot(Vector4 a, Vector4 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

bool Vector4::Approximately(Vector4 a, Vector4 b)
{
	return WaveMath::Approximately(a.x, b.x) && WaveMath::Approximately(a.y, b.y) && WaveMath::Approximately(a.z, b.z) && WaveMath::Approximately(a.w, b.w);
}

Vector4 operator*(float scalar, Vector4 vector)
{
	return vector * scalar;
}

Vector4 operator/(float scalar, Vector4 vector)
{
	return vector / scalar;
}
