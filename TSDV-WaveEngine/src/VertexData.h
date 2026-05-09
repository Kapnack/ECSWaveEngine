#pragma once

#include "WaveMath/Vector2/Vector2.h"
#include "WaveMath/Vector3/Vector3.h"
#include "Material/Color/Color.h";

#include "Export.h"

using namespace std;

WAVEEXPORT struct VertexData
{
	Vector3 position;

	Color color;

	Vector2 textureCordinates;

	Vector3 normal;

	WAVEEXPORT VertexData();
	WAVEEXPORT VertexData(const float& v1, const float& v2, const float& v3, const float& r, const float& g, const float& b, const float& a);
	WAVEEXPORT VertexData(const Vector3& position, const Color& color);
	WAVEEXPORT VertexData(const Vector3& position, const Color& color, const Vector2& textureCordinates);
	WAVEEXPORT VertexData(const Vector3& position, const Color& color, const Vector2& textureCordinates, const Vector3& normal);

	WAVEEXPORT void SetColor(const Color& color);
};