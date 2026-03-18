#pragma once

#include "Export.h"

WAVEEXPORT struct Vector4
{
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 0.0f;

	WAVEEXPORT Vector4();
	WAVEEXPORT Vector4(float r, float g, float b, float a);
};

static const Vector4 Purple(0.5f, 0.0f, 0.5f, 1.0f);