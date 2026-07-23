#include "Vector3.h"

#include <cmath>
#include <cfloat>

#include "Wavemath/Vector2/Vector2.h"

const float Vector3::epsilon = 1e-05f;

Vector3::Vector3()
{
	*this = Zero();
}

Vector3::Vector3(const Vector3& vector3)
{
	x = vector3.x;
	y = vector3.y;
	z = vector3.z;
}

Vector3::Vector3(Vector2 vector2)
{
	x = vector2.x;
	y = vector2.y;
	z = 0.0f;
}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void Vector3::ClampMagnitude(float maxLength)
{
	*this = ClampMagnitude(*this, maxLength);
}

float Vector3::Magnitude() const
{
	return Vector3::Magnitude(*this);
}

float Vector3::SqrMagnitude() const
{
	return Vector3::SqrMagnitude(*this);
}

void Vector3::Normalize()
{
	*this = Normalized();
}

Vector3 Vector3::Normalized() const
{
	return Normalized(*this);
}

void Vector3::MoveToWards(Vector3 to, float distance)
{
	*this = MoveToWards(*this, to, distance);
}

Vector3 Vector3::operator/(Vector3 other) const
{
	return Vector3(x / other.x, y / other.y, z / other.z);
}

Vector3 Vector3::operator/(float scalar) const
{
	return Vector3(x / scalar, y / scalar, z / scalar);
}

Vector3 operator/(float scalar, Vector3 vector)
{
	return vector / scalar;
}

void Vector3::operator/=(float scalar)
{
	*this = *this / scalar;
}

Vector3 Vector3::operator+(Vector3 other) const
{
	return Vector3(x + other.x, y + other.y, z + other.z);
}

void Vector3::operator+=(Vector3 other)
{
	*this = *this + other;
}

Vector3 Vector3::operator-(Vector3 other) const
{
	return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}

void Vector3::operator-=(Vector3 other)
{
	*this = *this - other;
}

void Vector3::operator=(Vector2 vector2)
{
	x = vector2.x;
	y = vector2.y;
}

Vector3 Vector3::operator*(float scalar) const
{
	return Vector3(x * scalar, y * scalar, z * scalar);
}

Vector3 operator*(float scalar, Vector3 vector3)
{
	return vector3 * scalar;
}

void Vector3::operator*=(float scalar)
{
	*this = *this * scalar;
}

Vector3 Vector3::X()
{
	return Vector3(1.0f, 0.0f, 0.0f);
}

Vector3 Vector3::Y()
{
	return Vector3(0.0f, 1.0f, 0.0f);
}

Vector3 Vector3::Z()
{
	return Vector3(0.0f, 0.0f, 1.0f);
}

Vector3 Vector3::One()
{
	return Vector3(1.0f, 1.0f, 1.0f);
}

Vector3 Vector3::Up()
{
	return Y();
}

Vector3 Vector3::Down()
{
	return -Y();
}

Vector3 Vector3::Right()
{
	return X();
}

Vector3 Vector3::Left()
{
	return -X();
}

Vector3 Vector3::Foward()
{
	return Z();
}

Vector3 Vector3::Back()
{
	return -Z();
}

Vector3 Vector3::Zero()
{
	return Vector3(0.0f, 0.0f, 0.0f);
}

Vector3 Vector3::Max()
{
	return Vector3(FLT_MAX, FLT_MAX, FLT_MAX);
}

Vector3 Vector3::NMax()
{
	return -Max();
}

Vector3 Vector3::Min()
{
	return Vector3(FLT_MIN, FLT_MIN, FLT_MIN);
}

Vector3 Vector3::NMin()
{
	return -Min();
}

float Vector3::Angle(Vector3 from, Vector3 to)
{
	float dot = Dot(from, to);

	float magFrom = Magnitude(from);
	float magTo = Magnitude(to);

	if (magFrom == 0 || magTo == 0)
	{

		return 0.0f;
	}

	float cosTheta = dot / (magFrom * magTo);

	cosTheta = cosTheta < -1.0f ? -1.0f : cosTheta > 1.0f ? 1.0f : cosTheta;

	return std::acos(cosTheta);
}

Vector3 Vector3::ClampMagnitude(Vector3 vector, float maxLength)
{
	float sqrMag = SqrMagnitude(vector);

	if (sqrMag > maxLength * maxLength)
	{
		float mag = std::sqrt(sqrMag);
		float scale = maxLength / mag;

		return Vector3(vector.x * scale, vector.y * scale, vector.z * scale);
	}

	return vector;
}


Vector3 Vector3::Cross(Vector3 a, Vector3 b)
{
	return Vector3
	(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	);
}

float Vector3::Magnitude(Vector3 vector)
{
	return std::sqrtf(SqrMagnitude(vector));
}

float Vector3::SqrMagnitude(Vector3 vector)
{
	return Dot(vector, vector);
}

float Vector3::Dot(Vector3 a, Vector3 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 Vector3::Lerp(Vector3 a, Vector3 b, float t)
{
	t = t < -1.0f ? -1.0f : t > 1.0f ? 1.0f : t;

	return LerpUnclamp(a, b, t);
}

Vector3 Vector3::LerpUnclamp(Vector3 a, Vector3 b, float t)
{
	return Vector3(a + (b - a) * t);
}

float Vector3::Distance(Vector3 a, Vector3 b)
{
	return (a - b).Magnitude();
}

Vector3 Vector3::Max(Vector3 a, Vector3 b)
{
	float x = a.x > b.x ? a.x : b.x;
	float y = a.y > b.y ? a.y : b.y;
	float z = a.z > b.z ? a.z : b.z;

	return Vector3(x, y, z);
}

Vector3 Vector3::Min(Vector3 a, Vector3 b)
{
	float x = a.x < b.x ? a.x : b.x;
	float y = a.y < b.y ? a.y : b.y;
	float z = a.z < b.z ? a.z : b.z;

	return Vector3(x, y, z);
}

Vector3 Vector3::Project(Vector3 a, Vector3 b)
{
	float dot = Dot(a, b);
	float sqrMag = SqrMagnitude(b);

	if (sqrMag < epsilon * epsilon)
		return Vector3::Zero();

	float scale = dot / sqrMag;
	return b * scale;
}

Vector3 Vector3::Normalized(Vector3 a)
{
	float mag = a.Magnitude();

	if (mag < epsilon)
		return Vector3::Zero();

	if (abs(mag - 1.0f) < epsilon)
		return a;

	return a / mag;
}

Vector3 Vector3::MoveToWards(Vector3 from, Vector3 to, float distance)
{
	Vector3 toVector = to - from;

	float sqDist = toVector.SqrMagnitude();

	if (sqDist <= distance * distance)
		return to;

	float dist = std::sqrt(sqDist);

	return from + toVector / dist * distance;
}

Vector3 Vector3::Reflect(Vector3 direction, Vector3 normal)
{
	float dot = Dot(direction, normal);
	return direction - normal * (2.0f * dot);
}
