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
	WAVEEXPORT Vector3(const Vector3& vector3);
	WAVEEXPORT Vector3(Vector2 vector2);
	WAVEEXPORT Vector3(float x, float y, float z = 0.0f);
	WAVEEXPORT void ClampMagnitude(float maxLength);
	WAVEEXPORT float Magnitude() const;
	WAVEEXPORT float SqrMagnitude() const;
	WAVEEXPORT void Normalize();
	WAVEEXPORT Vector3 Normalized() const;
	WAVEEXPORT void MoveToWards(Vector3 to, float distance);

	WAVEEXPORT Vector3 operator/(Vector3 other) const;
	WAVEEXPORT Vector3 operator/(float scalar) const;
	WAVEEXPORT friend Vector3 operator/(float scalar, Vector3 other);
	WAVEEXPORT void operator/=(float scalar);
	WAVEEXPORT Vector3 operator+(Vector3 other) const;
	WAVEEXPORT void operator+=(Vector3 other);
	WAVEEXPORT Vector3 operator-(Vector3 other) const;
	WAVEEXPORT Vector3 operator-() const;
	WAVEEXPORT void operator-=(Vector3 other);
	WAVEEXPORT void operator=(Vector2 vector2);
	WAVEEXPORT Vector3 operator*(float scalar) const;
	WAVEEXPORT friend Vector3 operator*(float scalar, Vector3 vector3);
	WAVEEXPORT void operator*=(float scalar);

	WAVEEXPORT static Vector3 X();
	WAVEEXPORT static Vector3 Y();
	WAVEEXPORT static Vector3 Z();
	WAVEEXPORT static Vector3 Up();
	WAVEEXPORT static Vector3 Down();
	WAVEEXPORT static Vector3 Right();
	WAVEEXPORT static Vector3 Left();
	WAVEEXPORT static Vector3 One();
	WAVEEXPORT static Vector3 Foward();
	WAVEEXPORT static Vector3 Back();
	WAVEEXPORT static Vector3 Zero();
	WAVEEXPORT static Vector3 Max();
	WAVEEXPORT static Vector3 NMax();
	WAVEEXPORT static Vector3 Min();
	WAVEEXPORT static Vector3 NMin();

	WAVEEXPORT static float Angle(Vector3 from, Vector3 to);
	WAVEEXPORT static Vector3 ClampMagnitude(Vector3 vector, float maxLength);
	WAVEEXPORT static Vector3 Cross(Vector3 a, Vector3 b);
	WAVEEXPORT static float Magnitude(Vector3 vector);
	WAVEEXPORT static float SqrMagnitude(Vector3 vector);
	WAVEEXPORT static float Dot(Vector3 a, Vector3 b);
	WAVEEXPORT static Vector3 Lerp(Vector3 a, Vector3 b, float t);
	WAVEEXPORT static Vector3 LerpUnclamp(Vector3 a, Vector3 b, float t);
	WAVEEXPORT static float Distance(Vector3 a, Vector3 b);
	WAVEEXPORT static Vector3 Max(Vector3 a, Vector3 b);
	WAVEEXPORT static Vector3 Min(Vector3 a, Vector3 b);
	WAVEEXPORT static Vector3 Project(Vector3 a, Vector3 b);
	WAVEEXPORT static Vector3 Normalized(Vector3 a);
	WAVEEXPORT static Vector3 MoveToWards(Vector3 from, Vector3 to, float distance);
	WAVEEXPORT Vector3 Reflect(Vector3 direction, Vector3 normal);
};