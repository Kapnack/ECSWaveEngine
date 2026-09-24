#include "Quaternion.h"

#include <cmath>
#include "WaveMath/WaveMath/WaveMath.h"

Quaternion::Quaternion()
{
	*this = Identity();
}

Quaternion::Quaternion(Vector3 eulerAngles)
{
	*this = Euler(eulerAngles);
}

Quaternion::Quaternion(Vector3 vector3, float w)
{
	this->x = vector3.x;
	this->y = vector3.y;
	this->z = vector3.z;
	this->w = w;
}

Quaternion::Quaternion(float x, float y, float z, float w)
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

Vector3 Quaternion::ToEuler() const
{
	return ToEuler(*this);
}

Quaternion Quaternion::operator+(Quaternion other) const
{
	return Quaternion(x + other.x, y + other.y, z + other.z, w + other.w);
}

void Quaternion::operator+=(Quaternion other)
{
	*this = *this + other;
}

Quaternion Quaternion::operator-(Quaternion other) const
{
	return Quaternion(x - other.x, y - other.y, z - other.z, w - other.w);
}

void Quaternion::operator-=(Quaternion other)
{
	*this = *this - other;
}

Vector3 Quaternion::operator*(Vector3 v) const
{
	Vector3 qVec(x, y, z);

	Vector3 t = 2.0f * Vector3::Cross(qVec, v);
	return v + w * t + Vector3::Cross(qVec, t);
}

Quaternion Quaternion::operator*(Quaternion other) const
{
	return Quaternion
	(
		w * other.x + x * other.w + y * other.z - z * other.y,
		w * other.y - x * other.z + y * other.w + z * other.x,
		w * other.z + x * other.y - y * other.x + z * other.w,
		w * other.w - x * other.x - y * other.y - z * other.z
	);
}

void Quaternion::operator*=(Quaternion other)
{
	*this = *this * other;
}

Quaternion Quaternion::operator*(float scalar) const
{
	return Quaternion(x * scalar, y * scalar, z * scalar, w * scalar);
}

Quaternion operator*(float scalar, Quaternion other)
{
	return other * scalar;
}

void Quaternion::operator*=(float scalar)
{
	*this = *this * scalar;
}

Quaternion Quaternion::operator/(float scalar) const
{
	return Quaternion(x / scalar, y / scalar, z / scalar, w / scalar);
}

Quaternion operator/(float scalar, Quaternion quaternion)
{
	return quaternion / scalar;
}

void Quaternion::operator/=(float scalar)
{
	*this = *this / scalar;
}

Quaternion Quaternion::Identity()
{
	return Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
}

float Quaternion::Magnitude(Quaternion a)
{
	return WaveMath::Sqrt(SqrMagnitude(a));
}

float Quaternion::SqrMagnitude(Quaternion a)
{
	return Dot(a, a);
}

float Quaternion::Dot(Quaternion a, Quaternion b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

Quaternion Quaternion::Normalized(Quaternion a)
{
	float sqrMag = SqrMagnitude(a);

	if (sqrMag < WaveMath::Epsilon() * WaveMath::Epsilon())
		return Identity();

	return a / WaveMath::Sqrt(sqrMag);
}

Quaternion Quaternion::AngleAxis(float angle, Vector3 axis)
{
	const float Deg2Rad = WaveMath::PI() / 180.0f;

	const float rad = angle * Deg2Rad;
	const float halfAngle = rad * 0.5f;

	return Quaternion(axis.Normalized() * std::sinf(halfAngle), std::cosf(halfAngle));
}

Quaternion Quaternion::Lerp(Quaternion a, Quaternion b, float t)
{
	t = t < 0.0f ? 0.0f : t > 1.0f ? 1.0f : t;

	return UnclampLerp(a, b, t);
}

Quaternion Quaternion::Slerp(Quaternion a, Quaternion b, float t)
{
	t = t < 0.0f ? 0.0f : t > 1.0f ? 1.0f : t;

	float dot = Dot(a, b);

	// If dot is negative, negate one quaternion to take the shorter arc
	Quaternion b2 = dot < 0.0f ? b * -1.0f : b;
	dot = WaveMath::Abs(dot);

	if (dot > 0.9995f)
		return Normalized(a + (b2 - a) * t); // Nearly identical — linear is fine

	float theta0 = std::acos(dot);
	float theta = theta0 * t;
	float s0 = std::cos(theta) - dot * std::sin(theta) / std::sin(theta0);
	float s1 = std::sin(theta) / std::sin(theta0);

	return Normalized(a * s0 + b2 * s1);
}

Quaternion Quaternion::UnclampLerp(Quaternion a, Quaternion b, float t)
{
	return a + (b - a) * t;
}

Quaternion Quaternion::Euler(float x, float y, float z)
{
	Quaternion qx = AngleAxis(x, Vector3::Right()); // Pitch
	Quaternion qy = AngleAxis(y, Vector3::Up()); // Yaw
	Quaternion qz = AngleAxis(z, Vector3::Foward()); // Roll

	return (qz * qy * qx).Normalized();
}

Quaternion Quaternion::Euler(Vector3 eulerAngles)
{
	return Euler(eulerAngles.x, eulerAngles.y, eulerAngles.z);
}

Quaternion Quaternion::Euler(Vector2 eulerAngles)
{
	return Euler(eulerAngles.x, eulerAngles.y);
}

Vector3 Quaternion::ToEuler(Quaternion q)
{
	Vector3 euler;

	euler.x = atan2(
		2.0f * (q.w * q.x + q.y * q.z),
		1.0f - 2.0f * (q.x * q.x + q.y * q.y)
	);

	float sinPitch = 2.0f * (q.w * q.y - q.z * q.x);

	sinPitch = WaveMath::Clamp01(sinPitch);

	euler.y = asin(sinPitch);

	euler.z = atan2(
		2.0f * (q.w * q.z + q.x * q.y),
		1.0f - 2.0f * (q.y * q.y + q.z * q.z)
	);

	return Vector3::Rad2Deg(euler);
}

Quaternion Quaternion::Conjugate(Quaternion a)
{
	return Quaternion(-a.x, -a.y, -a.z, a.w);
}

Quaternion Quaternion::Inverse(Quaternion a)
{
	float sqrMag = SqrMagnitude(a);

	if (sqrMag < WaveMath::Epsilon() * WaveMath::Epsilon())
		return Quaternion::Identity();

	return Conjugate(a) / sqrMag;
}

Quaternion Quaternion::LookAt(Vector3 target)
{
	Vector3 forward = target.Normalized();
	Vector3 defaultForward = Vector3::Foward();

	float dot = Vector3::Dot(defaultForward, forward);

	if (dot > 0.9999f)
		return Identity();

	if (dot < -0.9999f)
		return AngleAxis(180.0f, Vector3::Up());

	Vector3 axis = Vector3::Cross(defaultForward, forward).Normalized();

	float clampedDot = dot < -1.0f ? -1.0f : dot > 1.0f ? 1.0f : dot;
	float angleRad = std::acos(clampedDot);
	float angleDeg = angleRad * (180.0f / WaveMath::PI());

	return AngleAxis(angleDeg, axis);
}