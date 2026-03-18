#pragma once

#include "Export.h"
#include "WaveMath/Vector3/Vector3.h"
#include "WaveMath/Vector2/Vector2.h"

WAVEEXPORT struct Quaternion final
{
	float x;
	float y;
	float z;
	float w;

	static const float epsilon;

	WAVEEXPORT Quaternion();
	WAVEEXPORT Quaternion(const Vector3& eulerAngles);
	WAVEEXPORT Quaternion(const Vector3& vector3, const float& w);
	WAVEEXPORT Quaternion(const float& x, const float& y, const float& z, const float& w);
	WAVEEXPORT ~Quaternion();
	WAVEEXPORT float Magnitude() const;
	WAVEEXPORT float SqrMagnitude() const;
	WAVEEXPORT void Normalize();
	WAVEEXPORT Quaternion Normalized() const;

	WAVEEXPORT Quaternion operator+(const Quaternion& other) const;
	WAVEEXPORT void operator+=(const Quaternion& other);
	WAVEEXPORT Quaternion operator-(const Quaternion& other) const;
	WAVEEXPORT void operator-=(const Quaternion& other);
	WAVEEXPORT Vector3 operator* (const Vector3& v) const;
	WAVEEXPORT Quaternion operator* (const Quaternion& other) const;
	WAVEEXPORT void operator*=(const Quaternion& other);
	WAVEEXPORT Quaternion operator*(const float& scalar) const;
	WAVEEXPORT friend Quaternion operator*(const float& scalar, const Quaternion& other);
	WAVEEXPORT void operator*=(const float& scalar);
	WAVEEXPORT Quaternion operator/(const float& scalar) const;
	WAVEEXPORT friend Quaternion operator/(const float& scalar, const Quaternion& quaternion);
	WAVEEXPORT void operator/=(const float& scalar);

	WAVEEXPORT static Quaternion Identity();

	WAVEEXPORT static float Magnitude(const Quaternion& a);
	WAVEEXPORT static float SqrMagnitude(const Quaternion& a);
	WAVEEXPORT static float Dot(const Quaternion& a, const Quaternion& b);
	WAVEEXPORT static Quaternion Normalized(const Quaternion& a);
	WAVEEXPORT static Quaternion AngleAxis(const float& angle, const Vector3& axis);
	WAVEEXPORT static Quaternion Lerp(const Quaternion& a, const Quaternion& b, float t);
	WAVEEXPORT static Quaternion UnclampLerp(const Quaternion& a, const Quaternion& b, const float& t);
	WAVEEXPORT static Quaternion Euler(const float& x, const float& y, const float& z = 0.0f);
	WAVEEXPORT static Quaternion Euler(const Vector3& eulerAngles);
	WAVEEXPORT static Quaternion Euler(const Vector2& eulerAngles);
	WAVEEXPORT static Quaternion Conjugate(const Quaternion& a);
	WAVEEXPORT static Quaternion Inverse(const Quaternion& a);
};

