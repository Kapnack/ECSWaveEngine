#include "VertexData.h"

namespace WaveEngine
{
	VertexData::VertexData()
	{
	}

	VertexData::VertexData(const VertexData& vertexData)
	{
		position = vertexData.position;
		color = vertexData.color;
		textureCordinates = vertexData.textureCordinates;
		normal = vertexData.normal;
		tangent = vertexData.tangent;
	}

	VertexData::VertexData(float x, float y, float z, float r, float g, float b, float a)
	{
		position.x = x;
		position.y = y;
		position.z = z;

		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
	}

	VertexData::VertexData(Vector3 position, Color color)
	{
		this->position = position;
		this->color = color;
	}

	VertexData::VertexData(Vector3 position, Color color, Vector2 textureCordinates)
	{
		this->position = position;
		this->color = color;
		this->textureCordinates = textureCordinates;
	}

	VertexData::VertexData(Vector3 position, Color color, Vector2 textureCordinates, Vector3 normal)
	{
		this->position = position;
		this->color = color;
		this->textureCordinates = textureCordinates;
		this->normal = normal;
	}

	void VertexData::SetColor(Color color)
	{
		this->color = color;
	}

	void VertexData::operator=(VertexData vertexData)
	{
		position = vertexData.position;
		color = vertexData.color;
		textureCordinates = vertexData.textureCordinates;
		normal = vertexData.normal;
		tangent = vertexData.tangent;
	}
}