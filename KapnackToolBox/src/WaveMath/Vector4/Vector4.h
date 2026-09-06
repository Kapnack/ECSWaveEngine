#pragma once

#include "Export.h"

struct WAVEEXPORT Vector4
{
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 0.0f;

	Vector4();
	Vector4(float x, float y, float z, float w);

	static Vector4 Zero();
	static Vector4 One();
	static Vector4 Min();
	static Vector4 NMin();
	static Vector4 Max();
	static Vector4 NMax();

	Vector4 operator-() const;
};