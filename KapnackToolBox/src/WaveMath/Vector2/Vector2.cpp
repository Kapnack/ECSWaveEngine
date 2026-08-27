#include "Vector2.h"

#include <cmath>
#include <cfloat>

#include "WaveMath/Vector3/Vector3.h"
#include "WaveMath/WaveMath/WaveMath.h"

Vector2::Vector2()
{
}

Vector2::Vector2(const Vector2& other)
{
	x = other.x;
	y = other.y;
}

Vector2::Vector2(Vector3 vector3)
{
	x = vector3.x;
	y = vector3.y;
}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

float Vector2::Magnitude() const
{
	return Magnitude(*this);
}

float Vector2::SqrMagnitude() const
{
	return SqrMagnitude(*this);
}

void Vector2::ClampMagnitude(float maxMagnitud)
{
	*this = ClampedMagnitude(maxMagnitud);
}

Vector2 Vector2::ClampedMagnitude(float maxMagnitud) const
{
	return ClampMagnitude(*this, maxMagnitud);
}

void Vector2::Normalize()
{
	*this = Normalized();
}

Vector2 Vector2::Normalized() const
{
	return Normalized(*this);
}

void Vector2::MoveToWards(Vector2 to, float distance)
{
	*this = MovedToWards(to, distance);
}

Vector2 Vector2::MovedToWards(Vector2 to, float distance) const
{
	return MoveToWards(*this, to, distance);
}

void Vector2::Reflect(Vector2 normal)
{
	*this = Reflected(normal);
}

Vector2 Vector2::Reflected(Vector2 normal) const
{
	return Reflect(*this, normal);
}

float Vector2::Magnitude(Vector2 vector)
{
	return WaveMath::Sqrt(SqrMagnitude(vector));
}

float Vector2::SqrMagnitude(Vector2 vector)
{
	return Dot(vector, vector);
}

float Vector2::Dot(Vector2 a, Vector2 b)
{
	return a.x * b.x + a.y * b.y;
}

float Vector2::Cross(Vector2 a, Vector2 b)
{
	return a.x * b.y - a.y * b.x;
}

Vector2 Vector2::Project(Vector2 a, Vector2 b)
{
	float dot = Dot(a, b);
	float sqrMag = SqrMagnitude(b);

	if (sqrMag < WaveMath::Epsilon() * WaveMath::Epsilon())
		return Vector2::Zero();

	float scale = dot / sqrMag;
	return b * scale;
}

Vector2 Vector2::Normalized(Vector2 vector)
{
	float mag = vector.Magnitude();

	if (mag < WaveMath::Epsilon())
		return Vector2::Zero();

	if (WaveMath::Abs(mag - 1.0f) < WaveMath::Epsilon())
		return vector;

	return vector / mag;
}

Vector2 Vector2::MoveToWards(Vector2 from, Vector2 to, float distance)
{
	Vector2 toVector = to - from;

	float sqDist = toVector.SqrMagnitude();

	if (sqDist <= distance * distance)
		return to;

	float dist = WaveMath::Sqrt(sqDist);

	return from + toVector / dist * distance;
}

Vector2 operator/(float scalar, Vector2 vector)
{
	return vector / scalar;
}

Vector2 operator*(float scalar, Vector2 vector)
{
	return Vector2(vector.x * scalar, vector.y * scalar);
}

void Vector2::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
}

void Vector2::operator-=(Vector2 other)
{
	x -= other.x;
	y -= other.y;
}

void Vector2::operator+=(Vector2 other)
{
	x += other.x;
	y += other.y;
}

void Vector2::operator/=(Vector2 other)
{
	x /= other.x;
	y /= other.y;
}

void Vector2::operator/=(float scalar)
{
	x /= scalar;
	y /= scalar;
}

void Vector2::operator=(Vector2 other)
{
	x = other.x;
	y = other.y;
}

void Vector2::operator=(Vector3 vector3)
{
	x = vector3.x;
	y = vector3.y;
}

Vector2 Vector2::operator-(Vector2 other) const
{
	return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator+(Vector2 other) const
{
	return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-() const
{
	return Vector2(-x, -y);
}

Vector2 Vector2::operator/(Vector2 other) const
{
	return Vector2(x / other.x, y / other.y);
}

Vector2 Vector2::operator/(float scalar) const
{
	return Vector2(x / scalar, y / scalar);
}

Vector2 Vector2::operator*(float scalar) const
{
	return Vector2(x * scalar, y * scalar);
}

Vector2 Vector2::operator*(Vector2 other) const
{
	return Vector2(x * other.x, y * other.y);
}

bool Vector2::operator>(Vector2 other) const
{
	return x > other.x && y > other.y;
}

bool Vector2::operator==(Vector2 other) const
{
	return x == other.x && y == other.y;
}

bool Vector2::operator>=(Vector2 other) const
{
	return *this > other || *this == other;
}

bool Vector2::operator<=(Vector2 other) const
{
	return *this < other || *this == other;
}

float Vector2::Angle(Vector2 from, Vector2 to)
{
	float dot = Dot(from, to);

	float magFrom = Magnitude(from);
	float magTo = Magnitude(to);

	if (magFrom == 0 || magTo == 0)
		return 0.0f;

	float cosTheta = dot / (magFrom * magTo);

	cosTheta = cosTheta < -1.0f ? -1.0f : cosTheta > 1.0f ? 1.0f : cosTheta;

	return std::acos(cosTheta);
}

Vector2 Vector2::ClampMagnitude(Vector2 vector, float maxMagnitud)
{
	float sqrMag = SqrMagnitude(vector);

	if (sqrMag > maxMagnitud * maxMagnitud)
	{
		float mag = WaveMath::Sqrt(sqrMag);
		float scale = maxMagnitud / mag;

		return Vector2(vector.x * scale, vector.y * scale);
	}

	return vector;
}

bool Vector2::operator<(Vector2 other) const
{
	return other > *this;
}

Vector2 Vector2::Lerp(Vector2 a, Vector2 b, float t)
{
	t = t < -1.0f ? -1.0f : t > 1.0f ? 1.0f : t;

	return LerpUnclamp(a, b, t);
}

Vector2 Vector2::LerpUnclamp(Vector2 a, Vector2 b, float t)
{
	return a + (b - a) * t;
}

Vector2 Vector2::Min(Vector2 vectorA, Vector2 vectorB)
{
	const float x = vectorA.x < vectorB.x ? vectorA.x : vectorB.x;
	const float y = vectorA.y < vectorB.y ? vectorA.y : vectorB.y;

	return Vector2(x, y);
}

Vector2 Vector2::Max(Vector2 vectorA, Vector2 vectorB)
{
	const float x = vectorA.x > vectorB.x ? vectorA.x : vectorB.x;
	const float y = vectorA.y > vectorB.y ? vectorA.y : vectorB.y;

	return Vector2(x, y);
}

float Vector2::Distance(Vector2 a, Vector2 b)
{
	return (a - b).Magnitude();
}

Vector2 Vector2::Reflect(Vector2 vector, Vector2 normal)
{
	float dot = Dot(vector, normal);
	return vector - normal * (2.0f * dot);
}

Vector2 Vector2::Zero()
{
	return Vector2(0.0f, 0.0f);
}

Vector2 Vector2::One()
{
	return Vector2(1.0f, 1.0f);
}

Vector2 Vector2::X()
{
	return Vector2(1.0f, 0.0f);
}

Vector2 Vector2::Y()
{
	return Vector2(0.0f, 1.0f);
}

Vector2 Vector2::Up()
{
	return Y();
}

Vector2 Vector2::Down()
{
	return -Y();
}

Vector2 Vector2::Right()
{
	return X();
}

Vector2 Vector2::Left()
{
	return -X();
}

Vector2 Vector2::Max()
{
	return Vector2(FLT_MAX, FLT_MAX);
}

Vector2 Vector2::NMax()
{
	return -Max();
}

Vector2 Vector2::Min()
{
	return Vector2(FLT_MIN, FLT_MIN);
}

Vector2 Vector2::NMin()
{
	return -Min();
}
