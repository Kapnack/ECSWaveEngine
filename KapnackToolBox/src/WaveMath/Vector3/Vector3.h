#pragma once

#include "Export.h"

struct Vector2;

WAVEEXPORT struct Vector3 final
{
	float x;
	float y;
	float z;

	static const float epsilon;

	WAVEEXPORT Vector3();
	WAVEEXPORT Vector3(const Vector2& vector2);
	WAVEEXPORT Vector3(const float& x, const float& y, const float& z = 0.0f);
	WAVEEXPORT void ClampMagnitude(const float& maxLength);
	WAVEEXPORT float Magnitude() const;
	WAVEEXPORT float SqrMagnitude() const;
	WAVEEXPORT void Normalize();
	WAVEEXPORT Vector3 Normalized() const;
	WAVEEXPORT void MoveToWards(const Vector3& to, const float& distance);

	WAVEEXPORT Vector3 operator/(const Vector3& other) const;
	WAVEEXPORT Vector3 operator/(const float& scalar) const;
	WAVEEXPORT friend Vector3 operator/(const float& scalar, const Vector3& other);
	WAVEEXPORT void operator/=(const float& scalar);
	WAVEEXPORT Vector3 operator+(const Vector3& other) const;
	WAVEEXPORT void operator+=(const Vector3& other);
	WAVEEXPORT Vector3 operator-(const Vector3& other) const;
	WAVEEXPORT void operator-=(const Vector3& other);
	WAVEEXPORT void operator=(const Vector2& vector2);
	WAVEEXPORT Vector3 operator*(const float& scalar) const;
	WAVEEXPORT friend Vector3 operator*(const float& scalar, const Vector3& vector3);
	WAVEEXPORT void operator*=(const float& scalar);

	WAVEEXPORT static Vector3 Up();
	WAVEEXPORT static Vector3 Down();
	WAVEEXPORT static Vector3 Right();
	WAVEEXPORT static Vector3 Left();
	WAVEEXPORT static Vector3 One();
	WAVEEXPORT static Vector3 Foward();
	WAVEEXPORT static Vector3 Back();
	WAVEEXPORT static Vector3 Zero();

	WAVEEXPORT static float Angle(const Vector3& from, const Vector3& to);
	WAVEEXPORT static Vector3 ClampMagnitude(const Vector3& vector, const float& maxLength);
	WAVEEXPORT static Vector3 Cross(const Vector3& a, const Vector3& b);
	WAVEEXPORT static float Magnitude(const Vector3& vector);
	WAVEEXPORT static float SqrMagnitude(const Vector3& vector);
	WAVEEXPORT static float Dot(const Vector3& a, const Vector3& b);
	WAVEEXPORT static Vector3 Lerp(const Vector3& a, const Vector3& b, float t);
	WAVEEXPORT static Vector3 LerpUnclamp(const Vector3& a, const Vector3& b, const float& t);
	WAVEEXPORT static float Distance(const Vector3& a, const Vector3& b);
	WAVEEXPORT static Vector3 Max(const Vector3& a, const Vector3& b);
	WAVEEXPORT static Vector3 Min(const Vector3& a, const Vector3& b);
	WAVEEXPORT static Vector3 Project(const Vector3& a, const Vector3& b);
	WAVEEXPORT static Vector3 Normalized(const Vector3& a);
	WAVEEXPORT static Vector3 MoveToWards(const Vector3& from, const Vector3& to, const float& distance);
	WAVEEXPORT Vector3 Reflect(const Vector3& direction, const Vector3& normal);
};