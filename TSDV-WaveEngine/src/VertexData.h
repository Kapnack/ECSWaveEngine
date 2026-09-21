#pragma once

#include "WaveMath/Vector2/Vector2.h"
#include "WaveMath/Vector3/Vector3.h"
#include "Material/Color/Color.h";

#include "Export.h"

using namespace std;

namespace WaveEngine
{
	struct WAVEEXPORT VertexData
	{
		Vector3 position;

		Color color;

		Vector2 textureCordinates;

		Vector3 normal;

		Vector3 tangent;

		VertexData();
		VertexData(const VertexData& vertexData);
		VertexData(float v1, float v2, float v3, float r, float g, float b, float a);
		VertexData(Vector3 position, Color color);
		VertexData(Vector3 position, Color color, Vector2 textureCordinates);
		VertexData(Vector3 position, Color color, Vector2 textureCordinates, Vector3 normal);

		void SetColor(Color color);

		void operator=(VertexData vertexData);
	};
}