#pragma once

#include "WaveMath/Vector2/Vector2.h"
#include "WaveMath/Vector3/Vector3.h"
#include "WaveMath/Vector4/Vector4.h"
#include "Export.h"

using namespace std;

struct TextureData
{
	float u = 0;
	float v = 0;

	WAVEEXPORT TextureData();
	WAVEEXPORT TextureData(float u, float v);
};

WAVEEXPORT struct VertexData
{
	Vector3 position;

	Vector4 color;

	Vector2 textureCordinates;

	Vector3 normal;

	WAVEEXPORT VertexData();
	WAVEEXPORT VertexData(float v1, float v2, float v3, float r, float g, float b, float a);
	WAVEEXPORT VertexData(Vector3 position, Vector4 color);
	WAVEEXPORT VertexData(Vector3 position, Vector4 color, Vector2 textureCordinates);
	WAVEEXPORT VertexData(Vector3 position, Vector4 color, Vector2 textureCordinates, Vector3 normal);

	WAVEEXPORT void SetColor(Vector4 color);
};