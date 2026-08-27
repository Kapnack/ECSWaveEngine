#pragma once

#include "Export.h"

struct Vector2;

struct WAVEEXPORT Vector3 final
{
	float x;
	float y;
	float z;

	Vector3();
	Vector3(const Vector3& vector3);
	Vector3(Vector2 vector2);
	Vector3(float x, float y, float z = 0.0f);

	float Magnitude() const;
	float SqrMagnitude() const;
	void ClampMagnitude(float maxMagnitude);
	Vector3 ClampedMagnitude(float maxMagnitude) const;
	void Normalize();
	Vector3 Normalized() const;
	void MoveToWards(Vector3 to, float distance);
	Vector3 MovedToWards(Vector3 to, float distance) const;
	void Reflect(Vector3 normal);
	Vector3 Reflected(Vector3 normal) const;

	Vector3 operator/(Vector3 other) const;
	Vector3 operator/(float scalar) const;
	friend Vector3 operator/(float scalar, Vector3 other);
	void operator/=(float scalar);
	Vector3 operator+(Vector3 other) const;
	void operator+=(Vector3 other);
	Vector3 operator-(Vector3 other) const;
	Vector3 operator-() const;
	void operator-=(Vector3 other);
	void operator=(Vector2 vector2);
	Vector3 operator*(float scalar) const;
	friend Vector3 operator*(float scalar, Vector3 vector3);
	void operator*=(float scalar);
	bool operator>(Vector3 other) const;
	bool operator<(Vector3 other) const;
	bool operator==(Vector3 other) const;

	static Vector3 X();
	static Vector3 Y();
	static Vector3 Z();
	static Vector3 Up();
	static Vector3 Down();
	static Vector3 Right();
	static Vector3 Left();
	static Vector3 One();
	static Vector3 Foward();
	static Vector3 Back();
	static Vector3 Zero();
	static Vector3 Max();
	static Vector3 NMax();
	static Vector3 Min();
	static Vector3 NMin();

	static float Angle(Vector3 from, Vector3 to);
	static Vector3 ClampMagnitude(Vector3 vector, float maxLength);
	static Vector3 Cross(Vector3 a, Vector3 b);
	static float Magnitude(Vector3 vector);
	static float SqrMagnitude(Vector3 vector);
	static float Dot(Vector3 a, Vector3 b);
	static Vector3 Lerp(Vector3 a, Vector3 b, float t);
	static Vector3 LerpUnclamp(Vector3 a, Vector3 b, float t);
	static float Distance(Vector3 a, Vector3 b);
	static Vector3 Max(Vector3 a, Vector3 b);
	static Vector3 Min(Vector3 a, Vector3 b);
	static Vector3 Project(Vector3 a, Vector3 b);
	static Vector3 Normalized(Vector3 a);
	static Vector3 MoveToWards(Vector3 from, Vector3 to, float distance);
	static Vector3 Reflect(Vector3 direction, Vector3 normal);
};