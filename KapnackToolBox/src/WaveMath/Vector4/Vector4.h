#pragma once

#include "Export.h"

WAVEEXPORT struct Vector4
{
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 0.0f;

	WAVEEXPORT Vector4();
	WAVEEXPORT Vector4(const float& r, const float& g, const float& b, const float& a);
};