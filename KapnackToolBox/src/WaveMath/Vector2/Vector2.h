#pragma once

#include "Export.h"

struct Vector3;

struct WAVEEXPORT Vector2 final
{
	float x = 0.0f;
	float y = 0.0f;

	Vector2();
	Vector2(const Vector2& other);
	Vector2(Vector3 vector3);
	Vector2(float x, float y);

	float Magnitude() const;
	float SqrMagnitude() const;
	void ClampMagnitude(float maxMagnitud);
	Vector2 ClampedMagnitude(float maxMagnitud) const;
	void Normalize();
	Vector2 Normalized() const;
	void MoveToWards(Vector2 to, float distance);
	Vector2 MovedToWards(Vector2 to, float distance) const;
	void Reflect(Vector2 normal);
	Vector2 Reflected(Vector2 normal) const;

	static float Magnitude(Vector2 vector);
	static float SqrMagnitude(Vector2 vector);
	static float Dot(Vector2 a, Vector2 b);
	static float Cross(Vector2 a, Vector2 b);
	static Vector2 Project(Vector2 a, Vector2 b);
	static Vector2 Normalized(Vector2 vector);
	static Vector2 MoveToWards(Vector2 from, Vector2 to, float distance);

	Vector2 operator+(Vector2 other) const;
	Vector2 operator-(Vector2 other) const;
	Vector2 operator-() const;
	Vector2 operator/(Vector2 other) const;
	Vector2 operator/(float scalar) const;
	friend Vector2 operator/(float scalar, Vector2 vector);
	Vector2 operator*(float scalar) const;
	Vector2 operator*(Vector2 other) const;
	friend Vector2 operator*(float scalar, Vector2 vector);
	void operator*=(float scalar);
	void operator-=(Vector2 other);
	void operator+=(Vector2 other);
	void operator/=(Vector2 other);
	void operator/=(float scalar);
	void operator=(Vector2 other);
	void operator=(Vector3 vector3);
	bool operator<(Vector2 other) const;
	bool operator>(Vector2 other) const;

	static float Angle(Vector2 from, Vector2 to);
	static Vector2 ClampMagnitude(Vector2 vector, float maxMagnitud);
	static Vector2 Lerp(Vector2 a, Vector2 b, float t);
	static Vector2 LerpUnclamp(Vector2 a, Vector2 b, float t);
	static Vector2 Min(Vector2 a, Vector2 b);
	static Vector2 Max(Vector2 a, Vector2 b);
	static float Distance(Vector2 a, Vector2 b);
	static Vector2 Reflect(Vector2 vector, Vector2 normal);

	static Vector2 Zero();
	static Vector2 One();
	static Vector2 X();
	static Vector2 Y();
	static Vector2 Up();
	static Vector2 Down();
	static Vector2 Right();
	static Vector2 Left();
	static Vector2 Max();
	static Vector2 NMax();
	static Vector2 Min();
	static Vector2 NMin();
};