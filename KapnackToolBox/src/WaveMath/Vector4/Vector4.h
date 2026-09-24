#pragma once

#include "Export.h"

struct Vector3;

struct WAVEEXPORT Vector4
{
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 0.0f;

	Vector4();
	Vector4(const Vector4& vector);
	Vector4(Vector3 vector);
	Vector4(float x, float y, float z, float w);

	float Magnitude() const;
	Vector4 Normalized() const;
	void Normalize();
	float Dot(Vector4 other) const;
	bool Approximately(Vector4 other) const;

	static Vector4 Zero();
	static Vector4 One();
	static Vector4 Min();
	static Vector4 NMin();
	static Vector4 Max();
	static Vector4 NMax();

	Vector4 operator+(Vector4 other) const;
	void operator+=(Vector4 other);
	Vector4 operator-() const;
	Vector4 operator-(Vector4 other) const;
	void operator-=(Vector4 other);
	Vector4 operator*(Vector4 other) const;
	Vector4 operator*(float scalar) const;
	friend Vector4 operator*(float scalar, Vector4 vector);
	void operator*=(Vector4 other);
	void operator*=(float scalar);
	Vector4 operator/(float scalar) const;
	friend Vector4 operator/(float scalar, Vector4 vector);
	void operator/=(float scalar);
	bool operator>(Vector4 other) const;
	bool operator<(Vector4 other) const;
	bool operator==(Vector4 other) const;
	bool operator!=(Vector4 other) const;
	bool operator>=(Vector4 other) const;
	bool operator<=(Vector4 other) const;

	static Vector4 Normalized(Vector4 vector);
	static float Distance(Vector4 a, Vector4 b);
	static float Magnitude(Vector4 vector);
	static float SqrMagnitude(Vector4 vector);
	static float Dot(Vector4 a, Vector4 b);
	static bool Approximately(Vector4 a, Vector4 b);
};