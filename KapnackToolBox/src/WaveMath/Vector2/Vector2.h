#pragma once

#include "Export.h"

struct Vector3;

WAVEEXPORT struct Vector2 final
{
	float x = 0.0f;
	float y = 0.0f;

	WAVEEXPORT	Vector2();
	WAVEEXPORT	Vector2(const Vector2& other);
	WAVEEXPORT	Vector2(const Vector3& vector3);
	WAVEEXPORT	Vector2(const float& x, const float& y);

	WAVEEXPORT	Vector2 operator/(const Vector2& other);
	WAVEEXPORT	Vector2 operator*(const float& scalar);
	WAVEEXPORT	friend Vector2 operator*(const float& scalar, const Vector2 vector2);
	WAVEEXPORT	void operator*=(const float& scalar);
	WAVEEXPORT	void operator=(const Vector2& other);
	WAVEEXPORT	void operator=(const Vector3& vector3);

	WAVEEXPORT	static Vector2 Up();
	WAVEEXPORT	static Vector2 Down();
	WAVEEXPORT	static Vector2 Right();
	WAVEEXPORT	static Vector2 Left();
};