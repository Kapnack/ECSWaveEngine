#include "Quaternion.h"

#include <cmath>

const float Quaternion::epsilon = 1e-05f;

Quaternion::Quaternion()
{
	*this = Identity();
}

Quaternion::Quaternion(const Vector3& eulerAngles)
{
	*this = Euler(eulerAngles);
}

Quaternion::Quaternion(const Vector3& vector3, const float& w)
{
	this->x = vector3.x;
	this->y = vector3.y;
	this->z = vector3.z;
	this->w = w;
}

Quaternion::Quaternion(const float& x, const float& y, const float& z, const float& w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Quaternion::~Quaternion()
{
}

float Quaternion::Magnitude() const
{
	return Magnitude(*this);
}

float Quaternion::SqrMagnitude() const
{
	return SqrMagnitude(*this);
}

void Quaternion::Normalize()
{
	*this = Normalized();
}

Quaternion Quaternion::Normalized() const
{
	return Normalized(*this);
}

Quaternion Quaternion::operator+(const Quaternion& other) const
{
	return Quaternion(x + other.x, y + other.y, z + other.z, w + other.w);
}

void Quaternion::operator+=(const Quaternion& other)
{
	*this = *this + other;
}

Quaternion Quaternion::operator-(const Quaternion& other) const
{
	return Quaternion(x - other.x, y - other.y, z - other.z, w - other.w);
}

void Quaternion::operator-=(const Quaternion& other)
{
	*this = *this - other;
}

Vector3 Quaternion::operator*(const Vector3& v) const
{
	Vector3 qVec(x, y, z);

	Vector3 t = 2.0f * Vector3::Cross(qVec, v);
	return v + w * t + Vector3::Cross(qVec, t);
}

Quaternion Quaternion::operator*(const Quaternion& other) const
{
	return Quaternion
	(
		w * other.x + x * other.w + y * other.z - z * other.y,
		w * other.y - x * other.z + y * other.w + z * other.x,
		w * other.z + x * other.y - y * other.x + z * other.w,
		w * other.w - x * other.x - y * other.y - z * other.z
	);
}

void Quaternion::operator*=(const Quaternion& other)
{
	*this = *this * other;
}

Quaternion Quaternion::operator*(const float& scalar) const
{
	return Quaternion(x * scalar, y * scalar, z * scalar, w * scalar);
}

Quaternion operator*(const float& scalar, const Quaternion& other)
{
	return other * scalar;
}

void Quaternion::operator*=(const float& scalar)
{
	*this = *this * scalar;
}

Quaternion Quaternion::operator/(const float& scalar) const
{
	return Quaternion(x / scalar, y / scalar, z / scalar, w / scalar);
}

Quaternion operator/(const float& scalar, const Quaternion& quaternion)
{
	return quaternion / scalar;
}

void Quaternion::operator/=(const float& scalar)
{
	*this = *this / scalar;
}

Quaternion Quaternion::Identity()
{
	return Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
}

float Quaternion::Magnitude(const Quaternion& a)
{
	return std::sqrt(SqrMagnitude(a));
}

float Quaternion::SqrMagnitude(const Quaternion& a)
{
	return Dot(a, a);
}

float Quaternion::Dot(const Quaternion& a, const Quaternion& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

Quaternion Quaternion::Normalized(const Quaternion& a)
{
	float sqrMag = SqrMagnitude(a);

	if (sqrMag < epsilon * epsilon)
		return Identity();

	return a / std::sqrt(sqrMag);
}

Quaternion Quaternion::AngleAxis(const float& angle, const Vector3& axis)
{
	const float PI = 3.14159274f;
	const float Deg2Rad = PI * 180.0f;

	const float rad = angle * Deg2Rad;
	const float halfAngle = rad * 0.5f;

	return Quaternion
	(
		axis.Normalized() * std::sinf(halfAngle),
		std::cosf(halfAngle)
	);
}

Quaternion Quaternion::Lerp(const Quaternion& a, const Quaternion& b, float t)
{
	t = t < -1.0f ? -1.0f : t > 1.0f ? 1.0f : t;

	return UnclampLerp(a, b, t);
}

Quaternion Quaternion::UnclampLerp(const Quaternion& a, const Quaternion& b, const float& t)
{
	return a + (b - a) * t;
}

Quaternion Quaternion::Euler(const float& x, const float& y, const float& z)
{
	Quaternion qx = AngleAxis(x, Vector3::Right()); // Pitch
	Quaternion qy = AngleAxis(y, Vector3::Up()); // Yaw
	Quaternion qz = AngleAxis(z, Vector3::Foward()); // Roll

	return (qz * qy * qx).Normalized();
}

Quaternion Quaternion::Euler(const Vector3& eulerAngles)
{
	return Euler(eulerAngles.x, eulerAngles.y, eulerAngles.z);
}

Quaternion Quaternion::Euler(const Vector2& eulerAngles)
{
	return Euler(eulerAngles.x, eulerAngles.y);
}

Quaternion Quaternion::Conjugate(const Quaternion& a)
{
	return Quaternion(-a.x, -a.y, -a.z, a.w);
}

Quaternion Quaternion::Inverse(const Quaternion& a)
{
	float sqrMag = SqrMagnitude(a);

	if (sqrMag < epsilon * epsilon)
		return Quaternion::Identity();

	return Conjugate(a) / sqrMag;
}
