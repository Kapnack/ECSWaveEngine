#pragma once

#include "WaveMath/Vector2/Vector2.h"
#include "WaveMath/Vector3/Vector3.h"
#include "Material/Color/Color.h";

#include "Export.h"

using namespace std;

namespace WaveEngine
{
	WAVEEXPORT struct VertexData
	{
		Vector3 position;

		Color color;

		Vector2 textureCordinates;

		Vector3 normal;

		Vector3 tangent;

		WAVEEXPORT VertexData();
		WAVEEXPORT VertexData(float v1, float v2, float v3, float r, float g, float b, float a);
		WAVEEXPORT VertexData(Vector3 position, Color color);
		WAVEEXPORT VertexData(Vector3 position, Color color, Vector2 textureCordinates);
		WAVEEXPORT VertexData(Vector3 position, Color color, Vector2 textureCordinates, Vector3 normal);

		WAVEEXPORT void SetColor(Color color);
	};
}