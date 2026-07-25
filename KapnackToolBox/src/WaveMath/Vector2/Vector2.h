#pragma once

#include "Export.h"

struct Vector3;

WAVEEXPORT struct Vector2 final
{
	float x = 0.0f;
	float y = 0.0f;

	WAVEEXPORT	Vector2();
	WAVEEXPORT	Vector2(const Vector2& other);
	WAVEEXPORT	Vector2(Vector3 vector3);
	WAVEEXPORT	Vector2(float x, float y);

	WAVEEXPORT	Vector2 operator/(Vector2 other);
	WAVEEXPORT	Vector2 operator*(float scalar);
	WAVEEXPORT	friend Vector2 operator*(float scalar, Vector2 vector2);
	WAVEEXPORT	void operator*=(float scalar);
	WAVEEXPORT	void operator=(Vector2 other);
	WAVEEXPORT	void operator=(Vector3 vector3);

	WAVEEXPORT	static Vector2 Zero();
	WAVEEXPORT	static Vector2 One();
	WAVEEXPORT	static Vector2 Up();
	WAVEEXPORT	static Vector2 Down();
	WAVEEXPORT	static Vector2 Right();
	WAVEEXPORT	static Vector2 Left();
};