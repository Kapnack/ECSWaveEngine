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
	Vector4(const Vector4& vector3);
	Vector4(Vector3 vector3);
	Vector4(float x, float y, float z, float w);

	float Magnitude();
	Vector4 Normalized();
	void Normalize();

	static Vector4 Zero();
	static Vector4 One();
	static Vector4 Min();
	static Vector4 NMin();
	static Vector4 Max();
	static Vector4 NMax();

	Vector4 operator-() const;
	Vector4 operator/(float scalar) const;
	void operator/=(float scalar);

	static Vector4 Normalized(Vector4 vector4);
	static float Magnitude(Vector4 vector4);
	static float SqrMagnitude(Vector4 vector4);
	static float Dot(Vector4 vector4A, Vector4 vector4B);
};